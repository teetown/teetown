/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "auto_map.h"

#include "editor.h"

#include <engine/console.h>
#include <engine/storage.h>

#include <vector>

void CTilesetMapper::Load(const json_value &rElement)
{
	for(unsigned i = 0; i < rElement.u.array.length; ++i)
	{
		if(rElement[i].u.object.length != 1)
			continue;

		// new rule set
		CRuleSet NewRuleSet;
		const char *pConfName = rElement[i].u.object.values[0].name;
		str_copy(NewRuleSet.m_aName, pConfName, sizeof(NewRuleSet.m_aName));
		const json_value &rStart = *(rElement[i].u.object.values[0].value);

		// get basetile
		const json_value &rBasetile = rStart["basetile"];
		if(rBasetile.type == json_integer)
			NewRuleSet.m_BaseTile = clamp((int)rBasetile.u.integer, 0, 255);
		else
			NewRuleSet.m_BaseTile = 1;

		// get rules
		const json_value &rRuleNode = rStart["rules"];
		for(unsigned j = 0; j < rRuleNode.u.array.length && j < MAX_RULES; j++)
		{
			// create a new rule
			CRule NewRule;

			// index
			const json_value &rIndex = rRuleNode[j]["index"];
			if(rIndex.type == json_integer)
				NewRule.m_Index = clamp((int)rIndex.u.integer, 0, 255);
			else
				NewRule.m_Index = 1;

			// random
			const json_value &rRandom = rRuleNode[j]["random"];
			if(rRandom.type == json_integer)
				NewRule.m_Random = clamp((int)rRandom.u.integer, 0, 99999);
			else
				NewRule.m_Random = 0;

			// rotate
			const json_value &rRotate = rRuleNode[j]["rotate"];
			if(rRotate.type == json_integer && (rRotate.u.integer == 90 || rRotate.u.integer == 180 || rRotate.u.integer == 270))
				NewRule.m_Rotation = rRotate.u.integer;
			else
				NewRule.m_Rotation = 0;

			// hflip
			const json_value &rHFlip = rRuleNode[j]["hflip"];
			if(rHFlip.type == json_integer)
				NewRule.m_HFlip = clamp((int)rHFlip.u.integer, 0, 1);
			else
				NewRule.m_HFlip = 0;

			// vflip
			const json_value &rVFlip = rRuleNode[j]["vflip"];
			if(rVFlip.type == json_integer)
				NewRule.m_VFlip = clamp((int)rVFlip.u.integer, 0, 1);
			else
				NewRule.m_VFlip = 0;

			// get rule's content
			const json_value &rCondition = rRuleNode[j]["condition"];
			if(rCondition.type == json_array)
			{
				for(unsigned k = 0; k < rCondition.u.array.length; k++)
				{
					CRuleCondition Condition;

					Condition.m_X = rCondition[k]["x"].u.integer;
					Condition.m_Y = rCondition[k]["y"].u.integer;
					const json_value &rValue = rCondition[k]["value"];
					if(rValue.type == json_string)
					{
						// the value is not an index, check if it's full or empty
						if(str_comp((const char *)rValue, "full") == 0)
							Condition.m_Value = CRuleCondition::FULL;
						else
							Condition.m_Value = CRuleCondition::EMPTY;
					}
					else if(rValue.type == json_integer)
						Condition.m_Value = clamp((int)rValue.u.integer, (int)CRuleCondition::EMPTY, 255);
					else
						Condition.m_Value = CRuleCondition::EMPTY;

					NewRule.m_vConditions.push_back(Condition);
				}
			}

			NewRuleSet.m_vRules.push_back(NewRule);
		}

		m_vRuleSets.push_back(NewRuleSet);
	}
}

const char *CTilesetMapper::GetRuleSetName(int Index) const
{
	if(Index < 0 || Index >= (int)m_vRuleSets.size())
		return "";

	return m_vRuleSets[Index].m_aName;
}

void CTilesetMapper::Proceed(CLayerTiles *pLayer, int ConfigID, RECTi Area)
{
	if(pLayer->m_Readonly || ConfigID < 0 || ConfigID >= (int)m_vRuleSets.size())
		return;

	const CRuleSet &Conf = m_vRuleSets[ConfigID];

	if(Conf.m_vRules.empty())
		return;

	pLayer->Clamp(&Area);

	int BaseTile = Conf.m_BaseTile;

	// auto map !
	int MaxIndex = pLayer->m_Width * pLayer->m_Height;
	for(int y = Area.y; y < Area.y + Area.h; y++)
		for(int x = Area.x; x < Area.x + Area.w; x++)
		{
			CTile *pTile = &(pLayer->m_pTiles[y * pLayer->m_Width + x]);
			if(pTile->m_Index == 0)
				continue;

			pTile->m_Index = BaseTile;

			for(int i = 0; i < (int)Conf.m_vRules.size(); ++i)
			{
				bool RespectRules = true;
				for(int j = 0; j < (int)Conf.m_vRules[i].m_vConditions.size() && RespectRules; ++j)
				{
					const CRuleCondition &Condition = Conf.m_vRules[i].m_vConditions[j];
					int CheckIndex = clamp((y + Condition.m_Y), 0, pLayer->m_Height - 1) * pLayer->m_Width + clamp((x + Condition.m_X), 0, pLayer->m_Width - 1);

					if(CheckIndex < 0 || CheckIndex >= MaxIndex)
						RespectRules = false;
					else
					{
						if(Condition.m_Value == CRuleCondition::EMPTY || Condition.m_Value == CRuleCondition::FULL)
						{
							if(pLayer->m_pTiles[CheckIndex].m_Index > 0 && Condition.m_Value == CRuleCondition::EMPTY)
								RespectRules = false;

							if(pLayer->m_pTiles[CheckIndex].m_Index == 0 && Condition.m_Value == CRuleCondition::FULL)
								RespectRules = false;
						}
						else
						{
							if(pLayer->m_pTiles[CheckIndex].m_Index != Condition.m_Value)
								RespectRules = false;
						}
					}
				}

				if(RespectRules && (Conf.m_vRules[i].m_Random <= 1 || (int)(random_float() * Conf.m_vRules[i].m_Random) == 1))
				{
					pTile->m_Index = Conf.m_vRules[i].m_Index;
					pTile->m_Flags = 0;

					// rotate
					if(Conf.m_vRules[i].m_Rotation == 90)
						pTile->m_Flags ^= TILEFLAG_ROTATE;
					else if(Conf.m_vRules[i].m_Rotation == 180)
						pTile->m_Flags ^= (TILEFLAG_HFLIP | TILEFLAG_VFLIP);
					else if(Conf.m_vRules[i].m_Rotation == 270)
						pTile->m_Flags ^= (TILEFLAG_HFLIP | TILEFLAG_VFLIP | TILEFLAG_ROTATE);

					// flip
					if(Conf.m_vRules[i].m_HFlip)
						pTile->m_Flags ^= pTile->m_Flags & TILEFLAG_ROTATE ? TILEFLAG_HFLIP : TILEFLAG_VFLIP;
					if(Conf.m_vRules[i].m_VFlip)
						pTile->m_Flags ^= pTile->m_Flags & TILEFLAG_ROTATE ? TILEFLAG_VFLIP : TILEFLAG_HFLIP;
				}
			}
		}

	m_pEditor->m_Map.m_Modified = true;
}

void CDoodadsMapper::Load(const json_value &rElement)
{
	for(unsigned i = 0; i < rElement.u.array.length; ++i)
	{
		if(rElement[i].u.object.length != 1)
			continue;

		// new rule set
		CRuleSet NewRuleSet;
		const char *pConfName = rElement[i].u.object.values[0].name;
		str_copy(NewRuleSet.m_aName, pConfName, sizeof(NewRuleSet.m_aName));
		const json_value &rStart = *(rElement[i].u.object.values[0].value);

		// get rules
		const json_value &rRuleNode = rStart["rules"];
		for(unsigned j = 0; j < rRuleNode.u.array.length && j < MAX_RULES; j++)
		{
			// create a new rule
			CRule NewRule;

			// startid
			const json_value &rStartid = rRuleNode[j]["startid"];
			if(rStartid.type == json_integer)
				NewRule.m_Rect.x = clamp((int)rStartid.u.integer, 0, 255);
			else
				NewRule.m_Rect.x = 1;

			// endid
			const json_value &rEndid = rRuleNode[j]["endid"];
			if(rEndid.type == json_integer)
				NewRule.m_Rect.y = clamp((int)rEndid.u.integer, 0, 255);
			else
				NewRule.m_Rect.y = 1;

			// broken, skip
			if(NewRule.m_Rect.x > NewRule.m_Rect.y)
				continue;

			// rx
			const json_value &rRx = rRuleNode[j]["rx"];
			if(rRx.type == json_integer)
				NewRule.m_RelativePos.x = rRx.u.integer;
			else
				NewRule.m_RelativePos.x = 0;

			// ry
			const json_value &rRy = rRuleNode[j]["ry"];
			if(rRy.type == json_integer)
				NewRule.m_RelativePos.y = rRy.u.integer;
			else
				NewRule.m_RelativePos.y = 0;

			// width
			NewRule.m_Size.x = absolute(NewRule.m_Rect.x - NewRule.m_Rect.y) % 16 + 1;
			// height
			NewRule.m_Size.y = floor((float)absolute(NewRule.m_Rect.x - NewRule.m_Rect.y) / 16) + 1;

			// random
			const json_value &rRandom = rRuleNode[j]["random"];
			if(rRandom.type == json_integer)
				NewRule.m_Random = clamp((int)rRandom.u.integer, 1, 99999);
			else
				NewRule.m_Random = 1;

			// hflip
			const json_value &rHFlip = rRuleNode[j]["hflip"];
			if(rHFlip.type == json_integer)
				NewRule.m_HFlip = clamp((int)rHFlip.u.integer, 0, 1);
			else
				NewRule.m_HFlip = 0;

			// vflip
			const json_value &rVFlip = rRuleNode[j]["vflip"];
			if(rVFlip.type == json_integer)
				NewRule.m_VFlip = clamp((int)rVFlip.u.integer, 0, 1);
			else
				NewRule.m_VFlip = 0;

			// location
			NewRule.m_Location = CRule::FLOOR;
			const json_value &rLocation = rRuleNode[j]["location"];
			if(rLocation.type == json_string)
			{
				if(str_comp((const char *)rLocation, "ceiling") == 0)
					NewRule.m_Location = CRule::CEILING;
				else if(str_comp((const char *)rLocation, "walls") == 0)
					NewRule.m_Location = CRule::WALLS;
			}

			NewRuleSet.m_vRules.push_back(NewRule);
		}

		m_vRuleSets.push_back(NewRuleSet);
	}

	// sort
	for(CRuleSet &RuleSet : m_vRuleSets)
	{
		std::stable_sort(RuleSet.m_vRules.begin(), RuleSet.m_vRules.end());
	}
}

const char *CDoodadsMapper::GetRuleSetName(int Index) const
{
	if(Index < 0 || Index >= (int)m_vRuleSets.size())
		return "";

	return m_vRuleSets[Index].m_aName;
}

void CDoodadsMapper::AnalyzeGameLayer()
{
	// the purpose of this is to detect game layer collision's edges to place doodads according to them

	// clear existing edges
	m_vvFloorIds.clear();
	m_vvCeilingIds.clear();
	m_vvRightWallIds.clear();
	m_vvLeftWallIds.clear();

	const CLayerGame &Layer = *m_pEditor->m_Map.m_pGameLayer;

	bool FloorKeepChaining = false;
	bool CeilingKeepChaining = false;
	int FloorChainId = 0;
	int CeilingChainId = 0;

	// floors and ceilings
	// browse up to down
	for(int y = 1; y < Layer.m_Height - 1; y++)
	{
		FloorKeepChaining = false;
		CeilingKeepChaining = false;

		for(int x = 1; x < Layer.m_Width - 1; x++)
		{
			const CTile &Tile = (Layer.m_pTiles[y * Layer.m_Width + x]);

			// empty, skip
			if(Tile.m_Index == 0)
			{
				FloorKeepChaining = false;
				CeilingKeepChaining = false;
				continue;
			}

			// check up
			int CheckIndex = (y - 1) * Layer.m_Width + x;

			// add a floor part
			if(Tile.m_Index == 1 && (Layer.m_pTiles[CheckIndex].m_Index == 0 || Layer.m_pTiles[CheckIndex].m_Index > ENTITY_OFFSET))
			{
				// create an new chain
				if(!FloorKeepChaining)
				{
					std::vector<int> vChain{y * Layer.m_Width + x};
					m_vvFloorIds.push_back(vChain);
					FloorChainId = (int)m_vvFloorIds.size() - 1;
					FloorKeepChaining = true;
				}
				else
				{
					// keep chaining
					m_vvFloorIds[FloorChainId].push_back(y * Layer.m_Width + x);
				}
			}
			else
				FloorKeepChaining = false;

			// check down
			CheckIndex = (y + 1) * Layer.m_Width + x;

			// add a ceiling part
			if(Tile.m_Index == 1 && (Layer.m_pTiles[CheckIndex].m_Index == 0 || Layer.m_pTiles[CheckIndex].m_Index > ENTITY_OFFSET))
			{
				// create an new chain
				if(!CeilingKeepChaining)
				{
					std::vector<int> vChain{y * Layer.m_Width + x};
					m_vvCeilingIds.push_back(vChain);
					CeilingChainId = (int)m_vvCeilingIds.size() - 1;
					CeilingKeepChaining = true;
				}
				else
				{
					// keep chaining
					m_vvCeilingIds[CeilingChainId].push_back(y * Layer.m_Width + x);
				}
			}
			else
				CeilingKeepChaining = false;
		}
	}

	bool RWallKeepChaining = false;
	bool LWallKeepChaining = false;
	int RWallChainId = 0;
	int LWallChainId = 0;

	// walls
	// browse left to right
	for(int x = 1; x < Layer.m_Width - 1; x++)
	{
		RWallKeepChaining = false;
		LWallKeepChaining = false;

		for(int y = 1; y < Layer.m_Height - 1; y++)
		{
			CTile *pTile = &(Layer.m_pTiles[y * Layer.m_Width + x]);

			if(pTile->m_Index == 0)
			{
				RWallKeepChaining = false;
				LWallKeepChaining = false;
				continue;
			}

			// check right
			int CheckIndex = y * Layer.m_Width + (x + 1);

			// add a right wall part
			if(pTile->m_Index == 1 && (Layer.m_pTiles[CheckIndex].m_Index == 0 || Layer.m_pTiles[CheckIndex].m_Index > ENTITY_OFFSET))
			{
				// create an new chain
				if(!RWallKeepChaining)
				{
					std::vector<int> vChain{y * Layer.m_Width + x};
					m_vvRightWallIds.push_back(vChain);
					RWallChainId = (int)m_vvRightWallIds.size() - 1;
					RWallKeepChaining = true;
				}
				else
				{
					// keep chaining
					m_vvRightWallIds[RWallChainId].push_back(y * Layer.m_Width + x);
				}
			}
			else
				RWallKeepChaining = false;

			// check left
			CheckIndex = y * Layer.m_Width + (x - 1);

			// add a left wall part
			if(pTile->m_Index == 1 && (Layer.m_pTiles[CheckIndex].m_Index == 0 || Layer.m_pTiles[CheckIndex].m_Index > ENTITY_OFFSET))
			{
				// create an new chain
				if(!LWallKeepChaining)
				{
					std::vector<int> vChain{y * Layer.m_Width + x};
					m_vvLeftWallIds.push_back(vChain);
					LWallChainId = (int)m_vvLeftWallIds.size() - 1;
					LWallKeepChaining = true;
				}
				else
				{
					// keep chaining
					m_vvLeftWallIds[LWallChainId].push_back(y * Layer.m_Width + x);
				}
			}
			else
				LWallKeepChaining = false;
		}
	}

	// clean up too small chains
	auto RemoveSmallChains = [](std::vector<std::vector<int>> &vvChains) {
		vvChains.erase(
			std::remove_if(vvChains.begin(), vvChains.end(),
				[](const std::vector<int> &vChain) {
					return vChain.size() < 3;
				}),
			vvChains.end());
		/* TODO: Use this in C++20
		std::erase_if(vvChains, [](const std::vector<int> &vChain) {
			return vChain.size() < 3;
		});
		*/
	};

	RemoveSmallChains(m_vvFloorIds);
	RemoveSmallChains(m_vvCeilingIds);
	RemoveSmallChains(m_vvRightWallIds);
	RemoveSmallChains(m_vvLeftWallIds);
}

void CDoodadsMapper::PlaceDoodads(CLayerTiles *pLayer, CRule *pRule, std::vector<std::vector<int>> *pPositions, int Amount, int LeftWall)
{
	if(pRule->m_Location == CRule::CEILING)
		pRule->m_RelativePos.y++;
	else if(pRule->m_Location == CRule::WALLS)
		pRule->m_RelativePos.x++;

	// left walls
	if(LeftWall)
	{
		pRule->m_HFlip ^= LeftWall;
		pRule->m_RelativePos.x--;
		pRule->m_RelativePos.x = -pRule->m_RelativePos.x;
		pRule->m_RelativePos.x -= pRule->m_Size.x - 1;
	}

	int MaxIndex = pLayer->m_Width * pLayer->m_Height;
	int RandomValue = pRule->m_Random * ((101.f - Amount) / 100.0f);

	if(pRule->m_Random == 1)
		RandomValue = 1;

	// allow diversity with high Amount
	if(pRule->m_Random > 1 && RandomValue <= 1)
		RandomValue = 2;

	for(int f = 0; f < (int)pPositions->size(); f++)
		for(int c = 0; c < (int)(*pPositions)[f].size(); c += pRule->m_Size.x)
		{
			if((pRule->m_Location == CRule::FLOOR || pRule->m_Location == CRule::CEILING) && (int)(*pPositions)[f].size() - c < pRule->m_Size.x)
				break;

			if(pRule->m_Location == CRule::WALLS && (int)(*pPositions)[f].size() - c < pRule->m_Size.y)
				break;

			if(RandomValue > 1 && !IAutoMapper::Random(RandomValue))
				continue;

			// where to put it
			int ID = (*pPositions)[f][c];

			// relative position
			ID += pRule->m_RelativePos.x;
			ID += pRule->m_RelativePos.y * pLayer->m_Width;

			for(int y = 0; y < pRule->m_Size.y; y++)
				for(int x = 0; x < pRule->m_Size.x; x++)
				{
					int Index = y * pLayer->m_Width + x + ID;
					if(Index <= 0 || Index >= MaxIndex)
						continue;

					pLayer->m_pTiles[Index].m_Index = pRule->m_Rect.x + y * 16 + x;
				}

			// hflip
			if(pRule->m_HFlip)
			{
				for(int y = 0; y < pRule->m_Size.y; y++)
					for(int x = 0; x < pRule->m_Size.x / 2; x++)
					{
						int Index = y * pLayer->m_Width + x + ID;
						if(Index <= 0 || Index >= MaxIndex)
							continue;

						int CheckIndex = Index + pRule->m_Size.x - 1 - x * 2;

						if(CheckIndex <= 0 || CheckIndex >= MaxIndex)
							continue;

						CTile Tmp = pLayer->m_pTiles[Index];
						pLayer->m_pTiles[Index] = pLayer->m_pTiles[CheckIndex];
						pLayer->m_pTiles[CheckIndex] = Tmp;
					}

				for(int y = 0; y < pRule->m_Size.y; y++)
					for(int x = 0; x < pRule->m_Size.x; x++)
					{
						int Index = y * pLayer->m_Width + x + ID;
						if(Index <= 0 || Index >= MaxIndex)
							continue;

						pLayer->m_pTiles[Index].m_Flags ^= TILEFLAG_VFLIP;
					}
			}

			// vflip
			if(pRule->m_VFlip)
			{
				for(int y = 0; y < pRule->m_Size.y / 2; y++)
					for(int x = 0; x < pRule->m_Size.x; x++)
					{
						int Index = y * pLayer->m_Width + x + ID;
						if(Index <= 0 || Index >= MaxIndex)
							continue;

						int CheckIndex = Index + (pRule->m_Size.y - 1 - y * 2) * pLayer->m_Width;

						if(CheckIndex <= 0 || CheckIndex >= MaxIndex)
							continue;

						CTile Tmp = pLayer->m_pTiles[Index];
						pLayer->m_pTiles[Index] = pLayer->m_pTiles[CheckIndex];
						pLayer->m_pTiles[CheckIndex] = Tmp;
					}

				for(int y = 0; y < pRule->m_Size.y; y++)
					for(int x = 0; x < pRule->m_Size.x; x++)
					{
						int Index = y * pLayer->m_Width + x + ID;
						if(Index <= 0 || Index >= MaxIndex)
							continue;

						pLayer->m_pTiles[Index].m_Flags ^= TILEFLAG_HFLIP;
					}
			}

			// make the place occupied
			if(RandomValue > 1)
			{
				std::vector<int> vChainBefore;
				std::vector<int> vChainAfter;

				for(int j = 0; j < c; j++)
					vChainBefore.push_back((*pPositions)[f][j]);

				int Size = pRule->m_Size.x;
				if(pRule->m_Location == CRule::WALLS)
					Size = pRule->m_Size.y;

				for(int j = c + Size; j < (int)(*pPositions)[f].size(); j++)
					vChainAfter.push_back((*pPositions)[f][j]);

				pPositions->erase(pPositions->begin() + f);

				// f changes, reset c
				c = -1;

				if(vChainBefore.size() > 1)
					pPositions->push_back(vChainBefore);
				if(vChainAfter.size() > 1)
					pPositions->push_back(vChainAfter);
			}
		}
}

void CDoodadsMapper::Proceed(CLayerTiles *pLayer, int ConfigID, int Amount)
{
	if(pLayer->m_Readonly || ConfigID < 0 || ConfigID >= (int)m_vRuleSets.size())
		return;

	AnalyzeGameLayer();

	CRuleSet &Conf = m_vRuleSets[ConfigID];

	if(Conf.m_vRules.empty())
		return;

	int MaxIndex = pLayer->m_Width * pLayer->m_Height;

	// clear tiles
	for(int i = 0; i < MaxIndex; i++)
	{
		pLayer->m_pTiles[i].m_Index = 0;
		pLayer->m_pTiles[i].m_Flags = 0;
	}

	// place doodads
	for(CRule &Rule : Conf.m_vRules)
	{
		// floors
		if(Rule.m_Location == CRule::FLOOR && !m_vvFloorIds.empty())
		{
			PlaceDoodads(pLayer, &Rule, &m_vvFloorIds, Amount);
		}

		// ceilings
		if(Rule.m_Location == CRule::CEILING && !m_vvCeilingIds.empty())
		{
			PlaceDoodads(pLayer, &Rule, &m_vvCeilingIds, Amount);
		}

		// right walls
		if(Rule.m_Location == CRule::WALLS && !m_vvRightWallIds.empty())
		{
			PlaceDoodads(pLayer, &Rule, &m_vvRightWallIds, Amount);
		}

		// left walls
		if(Rule.m_Location == CRule::WALLS && !m_vvLeftWallIds.empty())
		{
			PlaceDoodads(pLayer, &Rule, &m_vvLeftWallIds, Amount, 1);
		}
	}

	m_pEditor->m_Map.m_Modified = true;
}

/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef ENGINE_SHARED_CONFIG_VARIABLES_H
#define ENGINE_SHARED_CONFIG_VARIABLES_H
#undef ENGINE_SHARED_CONFIG_VARIABLES_H // this file will be included several times

MACRO_CONFIG_UTF8STR(PlayerName, player_name, MAX_NAME_ARRAY_SIZE, MAX_NAME_LENGTH, "nameless tee", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Name of the player")
MACRO_CONFIG_UTF8STR(PlayerClan, player_clan, MAX_CLAN_ARRAY_SIZE, MAX_CLAN_LENGTH, "", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Clan of the player")
MACRO_CONFIG_INT(PlayerCountry, player_country, -1, -1, 1000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Country of the player")
MACRO_CONFIG_STR(Password, password, 32, "", CFGFLAG_SAVE|CFGFLAG_CLIENT|CFGFLAG_SERVER, "Password to the server")
MACRO_CONFIG_STR(Logfile, logfile, 128, "", CFGFLAG_SAVE|CFGFLAG_CLIENT|CFGFLAG_SERVER, "Filename to log all output to")
MACRO_CONFIG_INT(LogfileTimestamp, logfile_timestamp, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT|CFGFLAG_SERVER, "Add a time stamp to the log file's name")
MACRO_CONFIG_INT(ConsoleOutputLevel, console_output_level, 0, 0, 2, CFGFLAG_SAVE|CFGFLAG_CLIENT|CFGFLAG_SERVER, "Adjusts the amount of information in the console")
MACRO_CONFIG_INT(ShowConsoleWindow, show_console_window, 1, 0, 3, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Show console window (0 = never, 1 = debug, 2 = release, 3 = always")

// client
MACRO_CONFIG_STR(ClVersionServer, cl_version_server, 100, "version.teeworlds.com", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Server to use to check for new versions")

MACRO_CONFIG_INT(ClPredict, cl_predict, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Use prediction for objects in the game world")
MACRO_CONFIG_INT(ClPredictPlayers, cl_predict_players, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Predict movements of other players")
MACRO_CONFIG_INT(ClPredictProjectiles, cl_predict_projectiles, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Predict position of projectiles")
MACRO_CONFIG_INT(ClNameplates, cl_nameplates, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show name plates")
MACRO_CONFIG_INT(ClNameplatesAlways, cl_nameplates_always, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Always show name plates disregarding of distance")
MACRO_CONFIG_INT(ClNameplatesTeamcolors, cl_nameplates_teamcolors, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Use team colors for name plates")
MACRO_CONFIG_INT(ClNameplatesSize, cl_nameplates_size, 50, 0, 100, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Size of the name plates from 0 to 100%")
MACRO_CONFIG_INT(ClAutoswitchWeapons, cl_autoswitch_weapons, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Auto switch weapon on pickup")

MACRO_CONFIG_INT(ClShowhud, cl_showhud, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show ingame HUD")
MACRO_CONFIG_INT(ClShowChat, cl_showchat, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show chat")
MACRO_CONFIG_INT(ClFilterchat, cl_filterchat, 0, 0, 2, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show chat messages from: 0=all, 1=friends only, 2=no one")
MACRO_CONFIG_INT(ClDisableWhisper, cl_disable_whisper, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Disable completely the whisper feature.")
MACRO_CONFIG_INT(ClShowsocial, cl_showsocial, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show social data like names, clans, chat etc.")
MACRO_CONFIG_INT(ClShowfps, cl_showfps, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show ingame FPS counter")
MACRO_CONFIG_INT(ClShowUserId, cl_show_user_id, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show the ID for every user")
MACRO_CONFIG_INT(ClAirjumpindicator, cl_airjumpindicator, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show double jump indicator")
MACRO_CONFIG_INT(ClShowWelcome, cl_show_welcome, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show initial set-up dialog")
MACRO_CONFIG_INT(ClMotdTime, cl_motd_time, 10, 0, 100, CFGFLAG_CLIENT | CFGFLAG_SAVE, "How long to show the server message of the day")
MACRO_CONFIG_INT(ClShowXmasHats, cl_show_xmas_hats, 1, 0, 2, CFGFLAG_CLIENT | CFGFLAG_SAVE, "0=never, 1=during christmas, 2=always")
MACRO_CONFIG_INT(ClShowEasterEggs, cl_show_easter_eggs, 1, 0, 2, CFGFLAG_CLIENT | CFGFLAG_SAVE, "0=never, 1=during easter, 2=always")
MACRO_CONFIG_INT(ClWarningTeambalance, cl_warning_teambalance, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Warn about team balance")
MACRO_CONFIG_INT(ClShowServerBroadcast, cl_show_server_broadcast, 1, 0, 1, CFGFLAG_SAVE | CFGFLAG_CLIENT, "Show server broadcast")
MACRO_CONFIG_INT(ClColoredBroadcast, cl_colored_broadcast, 1, 0, 1, CFGFLAG_SAVE | CFGFLAG_CLIENT, "Enable colored server broadcasts")

MACRO_CONFIG_INT(ClDynamicCamera, cl_dynamic_camera, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Switches camera mode. 0=static camera, 1=dynamic camera")
MACRO_CONFIG_INT(ClMouseDeadzone, cl_mouse_deadzone, 300, 0, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Zone that doesn't trigger the dynamic camera")
MACRO_CONFIG_INT(ClMouseFollowfactor, cl_mouse_followfactor, 60, 0, 200, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Trigger amount for the dynamic camera")
MACRO_CONFIG_INT(ClMouseMaxDistanceDynamic, cl_mouse_max_distance_dynamic, 1000, 1, 2000, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Mouse max distance, in dynamic camera mode")
MACRO_CONFIG_INT(ClMouseMaxDistanceStatic, cl_mouse_max_distance_static, 400, 1, 2000, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Mouse max distance, in static camera mode")
MACRO_CONFIG_INT(ClCameraSmoothness, cl_camera_smoothness, 0, 0, 100, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Camera movement speed. 0=instant, 100=slow and smooth")
MACRO_CONFIG_INT(ClCameraStabilizing, cl_camera_stabilizing, 0, 0, 100, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Amount of camera slowdown during cursor movement")

MACRO_CONFIG_INT(ClCpuThrottle, cl_cpu_throttle, 0, 0, 100, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Throttles the main thread")
MACRO_CONFIG_INT(ClLoadCountryFlags, cl_load_country_flags, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Load and show country flags")

MACRO_CONFIG_INT(ClAutoDemoRecord, cl_auto_demo_record, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Automatically record demos")
MACRO_CONFIG_INT(ClAutoDemoMax, cl_auto_demo_max, 10, 0, 1000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Maximum number of automatically recorded demos (0 = no limit)")
MACRO_CONFIG_INT(ClAutoScreenshot, cl_auto_screenshot, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Automatically take screenshot at game over screen")
MACRO_CONFIG_INT(ClAutoStatScreenshot, cl_auto_statscreenshot, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Automatically take screenshot of game statistics")
MACRO_CONFIG_INT(ClAutoScreenshotMax, cl_auto_screenshot_max, 10, 0, 1000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Maximum number of automatically created screenshots (0 = no limit)")

MACRO_CONFIG_INT(ClSaveServerPasswords, cl_save_server_passwords, 1, 0, 2, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Save server passwords (0 = never, 1 = only favorites, 2 = all servers)")

MACRO_CONFIG_STR(ClMenuMap, cl_menu_map, 64, "auto", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Background map in the menu, auto = automatic based on season")
MACRO_CONFIG_INT(ClShowMenuMap, cl_show_menu_map, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Display background map in the menu")
MACRO_CONFIG_INT(ClMenuAlpha, cl_menu_alpha, 25, 0, 75, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Transparency of the menu background")
MACRO_CONFIG_INT(ClRotationRadius, cl_rotation_radius, 30, 1, 500, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Menu camera rotation radius")
MACRO_CONFIG_INT(ClRotationSpeed, cl_rotation_speed, 40, 1, 120, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Menu camera rotations in seconds")
MACRO_CONFIG_INT(ClCameraSpeed, cl_camera_speed, 5, 1, 10, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Menu camera speed")

MACRO_CONFIG_INT(ClShowStartMenuImages, cl_show_start_menu_images, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Show start menu images")
MACRO_CONFIG_INT(ClSkipStartMenu, cl_skip_start_menu, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Skip the start menu")

MACRO_CONFIG_INT(ClHideSelfScore, cl_hide_self_score, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Hide player's score in the scoreboard")
MACRO_CONFIG_INT(ClStatboardInfos, cl_statboard_infos, 1259, 1, 2047, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Mask of info to display on the global statboard")
MACRO_CONFIG_INT(ClShowLocalTimeAlways, cl_show_local_time_always, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Always show local time")

MACRO_CONFIG_INT(ClLastVersionPlayed, cl_last_version_played, PREV_CLIENT_VERSION, 0, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Last version of the game that was played")

MACRO_CONFIG_STR(ClLanguagefile, cl_languagefile, 255, "", CFGFLAG_CLIENT | CFGFLAG_SAVE, "What language file to use")

// ui
MACRO_CONFIG_INT(UiBrowserPage, ui_browser_page, 5, 5, 8, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Interface serverbrowser page")
MACRO_CONFIG_INT(UiSettingsPage, ui_settings_page, 0, 0, 5, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Interface settings page")
MACRO_CONFIG_STR(UiServerAddress, ui_server_address, 64, "localhost:8303", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Interface server address (Internet page)")
MACRO_CONFIG_STR(UiServerAddressLan, ui_server_address_lan, 64, "localhost:8303", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Interface server address (LAN page)")
MACRO_CONFIG_INT(UiMousesens, ui_mousesens, 200, 1, 100000, CFGFLAG_SAVE | CFGFLAG_CLIENT, "Mouse sensitivity for menus/editor")
MACRO_CONFIG_INT(UiJoystickSens, ui_joystick_sens, 100, 1, 100000, CFGFLAG_SAVE | CFGFLAG_CLIENT, "Joystick sensitivity for menus/editor")
MACRO_CONFIG_INT(UiAutoswitchInfotab, ui_autoswitch_infotab, 1, 0, 1, CFGFLAG_SAVE | CFGFLAG_CLIENT, "Switch to the info tab when clicking on a server")
MACRO_CONFIG_INT(UiWideview, ui_wideview, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Extended menus GUI")

// editor
MACRO_CONFIG_INT(ClEditor, cl_editor, 0, 0, 1, CFGFLAG_CLIENT, "View the editor")
MACRO_CONFIG_INT(EdZoomTarget, ed_zoom_target, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Zoom to the current mouse target")
MACRO_CONFIG_INT(EdShowkeys, ed_showkeys, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Editor shows which keys are pressed")
MACRO_CONFIG_INT(EdColorGridInner, ed_color_grid_inner, 0xFFFFFF26, 0, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Color inner grid")
MACRO_CONFIG_INT(EdColorGridOuter, ed_color_grid_outer, 0xFF4C4C4C, 0, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Color outer grid")
MACRO_CONFIG_INT(EdColorQuadPoint, ed_color_quad_point, 0xFF0000FF, 0, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Color of quad points")
MACRO_CONFIG_INT(EdColorQuadPointHover, ed_color_quad_point_hover, 0xFFFFFFFF, 0, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Color of quad points when hovering over with the mouse cursor")
MACRO_CONFIG_INT(EdColorQuadPointActive, ed_color_quad_point_active, 0xFFFFFFFF, 0, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Color of active quad points")
MACRO_CONFIG_INT(EdColorQuadPivot, ed_color_quad_pivot, 0x00FF00FF, 0, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Color of the quad pivot")
MACRO_CONFIG_INT(EdColorQuadPivotHover, ed_color_quad_pivot_hover, 0xFFFFFFFF, 0, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Color of the quad pivot when hovering over with the mouse cursor")
MACRO_CONFIG_INT(EdColorQuadPivotActive, ed_color_quad_pivot_active, 0xFFFFFFFF, 0, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Color of the active quad pivot")
MACRO_CONFIG_INT(EdColorSelectionQuad, ed_color_selection_quad, 0xFFFFFFFF, 0, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Color of the selection area for a quad")
MACRO_CONFIG_INT(EdColorSelectionTile, ed_color_selection_tile, 0xFFFFFF66, 0, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Color of the selection area for a tile")

// skins
MACRO_CONFIG_INT(ClCustomizeSkin, cl_customize_skin, 0, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Use a customized skin")
MACRO_CONFIG_INT(PlayerColorBody, player_color_body, 0x1B6F74, 0, 0xFFFFFF, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Player body color")
MACRO_CONFIG_INT(PlayerColorMarking, player_color_marking, 0xFF0000FF, 0, 0, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Player marking color")
MACRO_CONFIG_INT(PlayerColorDecoration, player_color_decoration, 0x1B6F74, 0, 0xFFFFFF, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Player decoration color")
MACRO_CONFIG_INT(PlayerColorHands, player_color_hands, 0x1B759E, 0, 0xFFFFFF, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Player hands color")
MACRO_CONFIG_INT(PlayerColorFeet, player_color_feet, 0x1C873E, 0, 0xFFFFFF, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Player feet color")
MACRO_CONFIG_INT(PlayerColorEyes, player_color_eyes, 0x0000FF, 0, 0xFFFFFF, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Player eyes color")
MACRO_CONFIG_INT(PlayerUseCustomColorBody, player_use_custom_color_body, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles usage of custom colors for body")
MACRO_CONFIG_INT(PlayerUseCustomColorMarking, player_use_custom_color_marking, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles usage of custom colors for marking")
MACRO_CONFIG_INT(PlayerUseCustomColorDecoration, player_use_custom_color_decoration, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles usage of custom colors for decoration")
MACRO_CONFIG_INT(PlayerUseCustomColorHands, player_use_custom_color_hands, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles usage of custom colors for hands")
MACRO_CONFIG_INT(PlayerUseCustomColorFeet, player_use_custom_color_feet, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles usage of custom colors for feet")
MACRO_CONFIG_INT(PlayerUseCustomColorEyes, player_use_custom_color_eyes, 1, 0, 1, CFGFLAG_CLIENT | CFGFLAG_SAVE, "Toggles usage of custom colors for eyes")
MACRO_CONFIG_UTF8STR(PlayerSkin, player_skin, MAX_SKIN_ARRAY_SIZE, MAX_SKIN_LENGTH, "default", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Player skin")
MACRO_CONFIG_UTF8STR(PlayerSkinBody, player_skin_body, MAX_SKIN_ARRAY_SIZE, MAX_SKIN_LENGTH, "standard", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Player skin body")
MACRO_CONFIG_UTF8STR(PlayerSkinMarking, player_skin_marking, MAX_SKIN_ARRAY_SIZE, MAX_SKIN_LENGTH, "", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Player skin marking")
MACRO_CONFIG_UTF8STR(PlayerSkinDecoration, player_skin_decoration, MAX_SKIN_ARRAY_SIZE, MAX_SKIN_LENGTH, "", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Player skin decoration")
MACRO_CONFIG_UTF8STR(PlayerSkinHands, player_skin_hands, MAX_SKIN_ARRAY_SIZE, MAX_SKIN_LENGTH, "standard", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Player skin hands")
MACRO_CONFIG_UTF8STR(PlayerSkinFeet, player_skin_feet, MAX_SKIN_ARRAY_SIZE, MAX_SKIN_LENGTH, "standard", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Player skin feet")
MACRO_CONFIG_UTF8STR(PlayerSkinEyes, player_skin_eyes, MAX_SKIN_ARRAY_SIZE, MAX_SKIN_LENGTH, "standard", CFGFLAG_CLIENT | CFGFLAG_SAVE, "Player skin eyes")

// browser
MACRO_CONFIG_STR(BrFilterString, br_filter_string, 25, "", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Server browser filtering string")

MACRO_CONFIG_INT(BrSort, br_sort, 4, 0, 256, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sort criteria for the server browser")
MACRO_CONFIG_INT(BrSortOrder, br_sort_order, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sort order in the server browser")
MACRO_CONFIG_INT(BrMaxRequests, br_max_requests, 25, 0, 1000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Number of requests to use when refreshing server browser")

MACRO_CONFIG_INT(BrDemoSort, br_demo_sort, 0, 0, 2, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sort criteria for the demo browser")
MACRO_CONFIG_INT(BrDemoSortOrder, br_demo_sort_order, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sort order in the demo browser")

// sound
MACRO_CONFIG_INT(SndBufferSize, snd_buffer_size, 512, 128, 32768, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sound buffer size")
MACRO_CONFIG_INT(SndRate, snd_rate, 48000, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sound mixing rate")
MACRO_CONFIG_INT(SndEnable, snd_enable, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Enable sounds")
MACRO_CONFIG_INT(SndInit, snd_init, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Initialize sound systems")
MACRO_CONFIG_INT(SndMusic, snd_enable_music, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Play background music")
MACRO_CONFIG_INT(SndVolume, snd_volume, 100, 0, 100, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Sound volume")
MACRO_CONFIG_INT(SndNonactiveMute, snd_nonactive_mute, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Mute the application when inactive")
MACRO_CONFIG_INT(SndAsyncLoading, snd_async_loading, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Load sound files threaded")

// graphics
MACRO_CONFIG_INT(GfxScreen, gfx_screen, 0, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Screen index")
MACRO_CONFIG_INT(GfxScreenWidth, gfx_screen_width, 0, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Screen resolution width")
MACRO_CONFIG_INT(GfxScreenHeight, gfx_screen_height, 0, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Screen resolution height")
MACRO_CONFIG_INT(GfxBorderless, gfx_borderless, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Borderless window (not to be used with fullscreen)")
MACRO_CONFIG_INT(GfxFullscreen, gfx_fullscreen, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Fullscreen")
MACRO_CONFIG_INT(GfxClear, gfx_clear, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Clear screen before rendering")
MACRO_CONFIG_INT(GfxVsync, gfx_vsync, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Vertical sync")
MACRO_CONFIG_INT(GfxDisplayAllModes, gfx_display_all_modes, 0, 0, 0, CFGFLAG_SAVE|CFGFLAG_CLIENT, "List non-supported display modes")
MACRO_CONFIG_INT(GfxHighdpi, gfx_highdpi, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Use high dpi mode if available")
MACRO_CONFIG_INT(GfxTextureCompression, gfx_texture_compression, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Use texture compression")
MACRO_CONFIG_INT(GfxHighDetail, gfx_high_detail, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "High detail")
MACRO_CONFIG_INT(GfxTextureQuality, gfx_texture_quality, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Don't scale textures down")
MACRO_CONFIG_INT(GfxFsaaSamples, gfx_fsaa_samples, 0, 0, 16, CFGFLAG_SAVE|CFGFLAG_CLIENT, "FSAA Samples")
MACRO_CONFIG_INT(GfxFinish, gfx_finish, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Wait until the GPU has finished the current frame before starting the new one")
MACRO_CONFIG_INT(GfxAsyncRender, gfx_asyncrender, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Render asynchronously")
MACRO_CONFIG_INT(GfxMaxFps, gfx_maxfps, 144, 30, 2000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Maximum FPS (when Limit FPS is enabled)")
MACRO_CONFIG_INT(GfxLimitFps, gfx_limitfps, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Limit FPS")
MACRO_CONFIG_INT(GfxUseX11XRandRWM, gfx_use_x11xrandr_wm, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Let SDL use the X11 XRandR window manager")

MACRO_CONFIG_INT(GfxNoclip, gfx_noclip, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Disable clipping")

// input
MACRO_CONFIG_INT(InpGrab, inp_grab, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Disable OS mouse settings such as mouse acceleration, use raw mouse input mode")
MACRO_CONFIG_INT(InpMousesens, inp_mousesens, 200, 1, 100000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "In-game mouse sensitivity")

// gamepads
MACRO_CONFIG_INT(JoystickEnable, joystick_enable, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Enable joystick")
MACRO_CONFIG_STR(JoystickGUID, joystick_guid, 34, "", CFGFLAG_SAVE|CFGFLAG_CLIENT, "Joystick GUID which uniquely identifies the active joystick")
MACRO_CONFIG_INT(JoystickAbsolute, joystick_absolute, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Enable absolute joystick aiming ingame")
MACRO_CONFIG_INT(JoystickSens, joystick_sens, 100, 1, 100000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "In-game joystick sensitivity")
MACRO_CONFIG_INT(JoystickX, joystick_x, 0, 0, 12, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Joystick axis that controls X axis of cursor")
MACRO_CONFIG_INT(JoystickY, joystick_y, 1, 0, 12, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Joystick axis that controls Y axis of cursor")
MACRO_CONFIG_INT(JoystickTolerance, joystick_tolerance, 5, 0, 50, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Joystick axis tolerance to account for jitter")

// server
MACRO_CONFIG_STR(SvName, sv_name, 128, "unnamed server", CFGFLAG_SAVE|CFGFLAG_SERVER, "Server name")
MACRO_CONFIG_STR(SvHostname, sv_hostname, 128, "", CFGFLAG_SAVE|CFGFLAG_SERVER, "Server hostname")
MACRO_CONFIG_STR(Bindaddr, bindaddr, 128, "", CFGFLAG_SAVE|CFGFLAG_CLIENT|CFGFLAG_SERVER|CFGFLAG_MASTER, "Address to bind the client/server to")
MACRO_CONFIG_INT(SvPort, sv_port, 8303, 0, 0, CFGFLAG_SAVE|CFGFLAG_SERVER, "Port to use for the server")
MACRO_CONFIG_INT(SvExternalPort, sv_external_port, 0, 0, 0, CFGFLAG_SAVE|CFGFLAG_SERVER, "External port to report to the master servers")
MACRO_CONFIG_STR(SvMap, sv_map, 128, "dm1", CFGFLAG_SAVE|CFGFLAG_SERVER, "Map to use on the server")
MACRO_CONFIG_INT(SvMaxClients, sv_max_clients, 8, 1, MAX_CLIENTS, CFGFLAG_SAVE|CFGFLAG_SERVER, "Maximum number of clients that are allowed on a server")
MACRO_CONFIG_INT(SvMaxClientsPerIP, sv_max_clients_per_ip, 4, 1, MAX_CLIENTS, CFGFLAG_SAVE|CFGFLAG_SERVER, "Maximum number of clients with the same IP that can connect to the server")
MACRO_CONFIG_INT(SvMapDownloadSpeed, sv_map_download_speed, 8, 1, 16, CFGFLAG_SAVE|CFGFLAG_SERVER, "Number of map data packages a client gets on each request")
MACRO_CONFIG_INT(SvHighBandwidth, sv_high_bandwidth, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_SERVER, "Use high bandwidth mode. Doubles the bandwidth required for the server. LAN use only")
MACRO_CONFIG_INT(SvRegister, sv_register, 1, 0, 1, CFGFLAG_SAVE|CFGFLAG_SERVER, "Register server with master server for public listing")
MACRO_CONFIG_STR(SvRconPassword, sv_rcon_password, 32, "", CFGFLAG_SAVE|CFGFLAG_SERVER, "Remote console password (full access)")
MACRO_CONFIG_STR(SvRconModPassword, sv_rcon_mod_password, 32, "", CFGFLAG_SAVE|CFGFLAG_SERVER, "Remote console password for moderators (limited access)")
MACRO_CONFIG_INT(SvRconMaxTries, sv_rcon_max_tries, 3, 0, 100, CFGFLAG_SAVE|CFGFLAG_SERVER, "Maximum number of tries for remote console authentication")
MACRO_CONFIG_INT(SvRconBantime, sv_rcon_bantime, 5, 0, 1440, CFGFLAG_SAVE|CFGFLAG_SERVER, "The time a client gets banned if remote console authentication fails. 0 makes it just use kick")
MACRO_CONFIG_INT(SvAutoDemoRecord, sv_auto_demo_record, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_SERVER, "Automatically record demos")
MACRO_CONFIG_INT(SvAutoDemoMax, sv_auto_demo_max, 10, 0, 1000, CFGFLAG_SAVE|CFGFLAG_SERVER, "Maximum number of automatically recorded demos (0 = no limit)")
MACRO_CONFIG_STR(SvMaplist, sv_maplist, 32, "all", CFGFLAG_SAVE|CFGFLAG_SERVER, "Maplist for authed clients (none, standard, all)")

MACRO_CONFIG_INT(SvWarmup, sv_warmup, 0, -1, 1000, CFGFLAG_SAVE | CFGFLAG_SERVER, "Number of seconds to do warmup before match starts (0 disables, -1 all players ready)")
MACRO_CONFIG_INT(SvCountdown, sv_countdown, 0, -1, 1000, CFGFLAG_SAVE | CFGFLAG_SERVER, "Number of seconds to freeze the game in a countdown before match starts (0 enables only for survival gamemodes, -1 disables)")
MACRO_CONFIG_STR(SvMotd, sv_motd, 900, "", CFGFLAG_SAVE | CFGFLAG_SERVER, "Message of the day to display for the clients")
MACRO_CONFIG_INT(SvTeamdamage, sv_teamdamage, 0, 0, 1, CFGFLAG_SAVE | CFGFLAG_SERVER, "Team damage")
MACRO_CONFIG_STR(SvMaprotation, sv_maprotation, 768, "", CFGFLAG_SAVE | CFGFLAG_SERVER, "Maps to rotate between")
MACRO_CONFIG_INT(SvMatchesPerMap, sv_matches_per_map, 1, 1, 100, CFGFLAG_SAVE | CFGFLAG_SERVER, "Number of matches on each map before rotating")
MACRO_CONFIG_INT(SvMatchSwap, sv_match_swap, 1, 0, 1, CFGFLAG_SAVE | CFGFLAG_SERVER, "Swap teams between matches")
MACRO_CONFIG_INT(SvPowerups, sv_powerups, 1, 0, 1, CFGFLAG_SAVE | CFGFLAG_SERVER, "Allow powerups like ninja")
MACRO_CONFIG_INT(SvScorelimit, sv_scorelimit, 20, 0, 1000, CFGFLAG_SAVE | CFGFLAG_SERVER, "Score limit (0 disables)")
MACRO_CONFIG_INT(SvTimelimit, sv_timelimit, 0, 0, 1000, CFGFLAG_SAVE | CFGFLAG_SERVER, "Time limit in minutes (0 disables)")
MACRO_CONFIG_STR(SvGametype, sv_gametype, 32, "dm", CFGFLAG_SAVE | CFGFLAG_SERVER, "Game type (dm, tdm, ctf, lms, lts)")
MACRO_CONFIG_INT(SvTournamentMode, sv_tournament_mode, 0, 0, 2, CFGFLAG_SAVE | CFGFLAG_SERVER, "Tournament mode. When enabled, players joins the server as spectator (2=additional restricted spectator chat)")
MACRO_CONFIG_INT(SvPlayerReadyMode, sv_player_ready_mode, 0, 0, 1, CFGFLAG_SAVE | CFGFLAG_SERVER, "When enabled, players can pause/unpause the game and start the game on warmup via their ready state")
MACRO_CONFIG_INT(SvSpamprotection, sv_spamprotection, 1, 0, 1, CFGFLAG_SAVE | CFGFLAG_SERVER, "Spam protection")

MACRO_CONFIG_INT(SvRespawnDelayTDM, sv_respawn_delay_tdm, 3, 0, 10, CFGFLAG_SAVE | CFGFLAG_SERVER, "Time needed to respawn after death in tdm gametype")

MACRO_CONFIG_INT(SvPlayerSlots, sv_player_slots, 8, 0, MAX_PLAYERS, CFGFLAG_SAVE | CFGFLAG_SERVER, "Number of slots to reserve for players")
MACRO_CONFIG_INT(SvSkillLevel, sv_skill_level, 1, SERVERINFO_LEVEL_MIN, SERVERINFO_LEVEL_MAX, CFGFLAG_SAVE | CFGFLAG_SERVER, "Supposed player skill level")
MACRO_CONFIG_INT(SvTeambalanceTime, sv_teambalance_time, 1, 0, 1000, CFGFLAG_SAVE | CFGFLAG_SERVER, "How many minutes to wait before autobalancing teams")
MACRO_CONFIG_INT(SvInactiveKickTime, sv_inactivekick_time, 3, 0, 1000, CFGFLAG_SAVE | CFGFLAG_SERVER, "How many minutes to wait before taking care of inactive clients")
MACRO_CONFIG_INT(SvInactiveKick, sv_inactivekick, 2, 1, 3, CFGFLAG_SAVE | CFGFLAG_SERVER, "How to deal with inactive clients (1=move player to spectator, 2=move to free spectator slot/kick, 3=kick)")
MACRO_CONFIG_INT(SvInactiveKickSpec, sv_inactivekick_spec, 0, 0, 1, CFGFLAG_SAVE | CFGFLAG_SERVER, "Kick inactive spectators")

MACRO_CONFIG_INT(SvSilentSpectatorMode, sv_silent_spectator_mode, 1, 0, 1, CFGFLAG_SAVE | CFGFLAG_SERVER, "Mute join/leave message of spectator")

MACRO_CONFIG_INT(SvStrictSpectateMode, sv_strict_spectate_mode, 0, 0, 1, CFGFLAG_SAVE | CFGFLAG_SERVER, "Restricts information in spectator mode")
MACRO_CONFIG_INT(SvVoteSpectate, sv_vote_spectate, 1, 0, 1, CFGFLAG_SAVE | CFGFLAG_SERVER, "Allow voting to move players to spectators")
MACRO_CONFIG_INT(SvVoteSpectateRejoindelay, sv_vote_spectate_rejoindelay, 3, 0, 1000, CFGFLAG_SAVE | CFGFLAG_SERVER, "How many minutes to wait before a player can rejoin after being moved to spectators by vote")
MACRO_CONFIG_INT(SvVoteKick, sv_vote_kick, 1, 0, 1, CFGFLAG_SAVE | CFGFLAG_SERVER, "Allow voting to kick players")
MACRO_CONFIG_INT(SvVoteKickMin, sv_vote_kick_min, 0, 0, MAX_CLIENTS, CFGFLAG_SAVE | CFGFLAG_SERVER, "Minimum number of players required to start a kick vote")
MACRO_CONFIG_INT(SvVoteKickBantime, sv_vote_kick_bantime, 5, 0, 1440, CFGFLAG_SAVE | CFGFLAG_SERVER, "The time to ban a player if kicked by vote. 0 makes it just use kick")

MACRO_CONFIG_STR(EcBindaddr, ec_bindaddr, 128, "localhost", CFGFLAG_SAVE|CFGFLAG_ECON, "Address to bind the external console to. Anything but 'localhost' is dangerous")
MACRO_CONFIG_INT(EcPort, ec_port, 0, 0, 0, CFGFLAG_SAVE|CFGFLAG_ECON, "Port to use for the external console")
MACRO_CONFIG_STR(EcPassword, ec_password, 32, "", CFGFLAG_SAVE|CFGFLAG_ECON, "External console password")
MACRO_CONFIG_INT(EcBantime, ec_bantime, 0, 0, 1440, CFGFLAG_SAVE|CFGFLAG_ECON, "The time a client gets banned if econ authentication fails. 0 just closes the connection")
MACRO_CONFIG_INT(EcAuthTimeout, ec_auth_timeout, 30, 1, 120, CFGFLAG_SAVE|CFGFLAG_ECON, "Time in seconds before the the econ authentification times out")
MACRO_CONFIG_INT(EcOutputLevel, ec_output_level, 1, 0, 2, CFGFLAG_SAVE|CFGFLAG_ECON, "Adjusts the amount of information in the external console")

MACRO_CONFIG_INT(NetTcpAbortOnClose, net_tcp_abort_on_close, 0, 0, 1, CFGFLAG_SAVE|CFGFLAG_SERVER|CFGFLAG_ECON, "Aborts tcp connection on close")

// Debug
MACRO_CONFIG_INT(Debug, debug, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SERVER, "Debug mode")
MACRO_CONFIG_INT(DbgPref, dbg_pref, 0, 0, 1, CFGFLAG_SERVER, "Performance outputs")
MACRO_CONFIG_INT(DbgGraphs, dbg_graphs, 0, 0, 1, CFGFLAG_CLIENT, "Performance graphs")
MACRO_CONFIG_INT(DbgHitch, dbg_hitch, 0, 0, 0, CFGFLAG_SERVER, "Hitch warnings")
MACRO_CONFIG_INT(DbgResizable, dbg_resizable, 0, 0, 0, CFGFLAG_CLIENT, "Enables window resizing")
#ifdef CONF_DEBUG
MACRO_CONFIG_INT(DbgDummies, dbg_dummies, 0, 0, MAX_CLIENTS, CFGFLAG_SERVER, "") // this one can crash the server if not used correctly
MACRO_CONFIG_INT(DbgStress, dbg_stress, 0, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SERVER, "Stress systems")
MACRO_CONFIG_INT(DbgStressNetwork, dbg_stress_network, 0, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SERVER, "Stress network")
MACRO_CONFIG_STR(DbgStressServer, dbg_stress_server, 32, "localhost", CFGFLAG_CLIENT, "Server to stress")
#endif

MACRO_CONFIG_INT(DbgFocus, dbg_focus, 0, 0, 1, CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(DbgTuning, dbg_tuning, 0, 0, 1, CFGFLAG_CLIENT, "")

#endif

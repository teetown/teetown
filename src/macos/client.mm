#import <Cocoa/Cocoa.h>

extern "C" int TWMain(int argc, const char **argv);

static BOOL IsRunningInsideBundle(void)
{
	NSBundle *pBundle = [NSBundle mainBundle];
	if(!pBundle)
		return NO;
	NSString *pBundlePath = [pBundle bundlePath];
	if(!pBundlePath)
		return NO;
	return [[pBundlePath lastPathComponent] isEqualToString:@"TeeTown.app"];
}

int main(int argc, const char **argv)
{
	BOOL FinderLaunch = argc >= 2 && !strncmp(argv[1], "-psn", 4);

	if(IsRunningInsideBundle())
	{
		NSString *pResourcePath = [[NSBundle mainBundle] resourcePath];
		if(!pResourcePath)
			return -1;

		[[NSFileManager defaultManager] changeCurrentDirectoryPath:pResourcePath];
	}

	if(FinderLaunch)
	{
		const char *apArgv[2] = { argv[0], nullptr };
		return TWMain(1, apArgv);
	}
	else
		return TWMain(argc, argv);
}

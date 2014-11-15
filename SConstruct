mode = ARGUMENTS.get("mode", "release")
techdemos = ARGUMENTS.get("techdemos", 1)

if not (mode in ["debug", "release"]):
	print("Error: compilation mode must be either debug or release")
	Exit(1)

if not (techdemos in [0,  1]):
	print("Error: inclusion of techdemos must be either 1 (include) or 0 (not)")
	Exit(1)

debugcppflags = ["-Wall", "-g", "-std=c++11"]
releasecppflags = ["-O3", "-std=c++11"]

env = Environment()

Export("env", "mode", "debugcppflags", "releasecppflags")

env.SConsignFile()

SConscript("src/libheliocentric/SConscript")
if techdemos > 0:
	SConscript("techdemos/SConscript")

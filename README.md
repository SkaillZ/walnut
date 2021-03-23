# walnut

Game engine project based on [Hazel](https://github.com/TheCherno/Hazel)

## Building

Run premake with `./genproject.sh`, then `make`. This builds the engine and Sandbox libraries
and the player binary. macOS is currently supported.

## Running

Run the player binary with the path where the Sandbox library is generated, e.g. with
`./bin/Debug-macosx-x86_64/player/player bin/Debug-macosx-x86_64/sandbox/`. The argument must be the *path* where it is generated, not the file name.

## Hot reloading

If you want to hot reload with changes in the Sandbox library, simply run `make sandbox`. The player should automatically load the newly built library.

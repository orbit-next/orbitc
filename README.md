# orbitc

orbitc is a project to port OrbitV code from BASIC to C with minimal
modifications.

orbitc programs are not intended to be used directly in a terminal. Instead,
they are intended to be used in conjunction with an *graphics adapter*, such
as `orbit-ws`, which connects to an orbitc program via its `stdin` and
`stdout`.

Currently, only `orbit5v` is being ported, but there are plans to port the
entire OrbitV collection once the first port is successful.

Only POSIX platforms are supported, but support for other platforms can be
added with relative ease if necessary.

## Setup

Run `setup.sh` to set up the project root directory. This only needs to be
done once. Currently `setup.sh` only decompresses marstopoLG.RND.

To build the project, run `build.sh`. The build process currently only creates
the single executable file `orbitc` in the root directory. This can then be
used with a graphics adapter. Consult the documentation of the graphics 
adapter for details.

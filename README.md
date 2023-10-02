# CCOS-new
Another reboot of my OS, but this time I'm not a dumbass.
## Notice
The `arm32` architecture is not in active development. It is only a placeholder for its development later on.
## Building
There are two architectures that you can target: `i686` and `riscv32`. Run the following command to change the target architecture:
```sh
export HOSTARCH=i686
```
Change `i686` to `riscv32` to build the RISC-V kernel instead. You will need the respective toolchain for the architecture of your choice, so `i686-elf` for `i686` and `riscv32-elf` for `riscv32`.

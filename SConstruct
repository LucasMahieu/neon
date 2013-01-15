#This is the SCons build script to build the neon project.

SourceList = Split('''
    source/MCUinit.c
    source/__arm_end.c
    source/__arm_start.c
    source/interrupt.c
    source/power.c
    source/systick.c
    source/board.c
    source/uart.c
    source/main.c
    source/newlibStubs.c
    source/rtc.c
    freescale_source/__arm_eabi_init.c
    freescale_source/gcc_ctor_dtor.c
    freescale_source/ROMCopy.c
    ''') #Define list of file to compile


#env = DefaultEnvironment(Split('''
#    tools = ['gcc', 'gnulink']
#    CC = '/home/bklippenstein/sat/bin/arm-none-eabi-gcc'
#    PROGSUFFIX = 'elf'
#    LINK = 'home/bklippenstein/sat/bin/arm-none-eabi-ld'
#    LINKCOM ='$LINK $SOURCES $__RPATH $_LIBFLAGS $_LIBDIRFLAGS $LINKFLAGS -o $TARGET'
#    '''))
    # Set up default environment to use our cross compiler and output an elf file. Also adjust the linker command order.

env = DefaultEnvironment()
env['CC'] = '/home/bklippenstein/sat/bin/arm-none-eabi-gcc'
env['PROGSUFFIX'] = 'elf'
env['LINK'] = '/home/bklippenstein/sat/bin/arm-none-eabi-ld'
env['LINKCOM'] ='$LINK $SOURCES $_LIBFLAGS $_LIBDIRFLAGS $__RPATH $LINKFLAGS -o $TARGET'


print env.subst("The C compiler is: $CC")

env.Append(CCFLAGS = Split('''
    -nostdinc
    -O0
    -ffunction-sections
    -fdata-sections
    -Wall
    -fmessage-length=0
    -mcpu=cortex-m0
    -mthumb
    -mfloat-abi=soft
    -g3
    -gdwarf-2
    -gstrict-dwarf
    -Wno-unused-but-set-variable
    ''')) #Set compiler flags to use.
    
env.Append(CPPPATH = Split('''
    include
    freescale_source
    freescale_include
    ../../sat/arm-none-eabi/lib/thumb/cortex-m0/
    ../../sat/lib/gcc/arm-none-eabi/4.7.3/thumb/cortex-m0
    ../../sat/arm-none-eabi/include
    ../../sat/arm-none-eabi/include/sys/
    ../../sat/lib/
    ../../sat/lib/gcc/arm-none-eabi/4.6.2/plugin/include/c
    ''')) #Set include directories for GCC
    #../../sat/arm-none-eabi/lib/thumb/cortex-m0/
    #../../Freescale/MCU/ARM_GCC_Support/ewl/lib/armv6-m/
    #../../Freescale/Cross_Tools/arm-none-eabi-gcc-4_6_2/lib/gcc/arm-none-eabi/4.6.2/armv6-m/
    #objects
env.Append(LINKFLAGS = Split('''
    -nostartfiles
    -nostdlib
    --gc-sections
    --start-group
    --end-group
    -Map neon.map
    -n
    -Tsource/MKL25Z128_flash.ld
    ''')) #Set linker flags to use.
    #    -nodefaultlibs
env.Append(LIBS = Split('''
    libnosys
    libc
    libm
    libgcc
    '''))

env.Append(LIBPATH = Split('''
    ../../sat/arm-none-eabi/lib/thumb/cortex-m0/
    ../../sat/lib/gcc/arm-none-eabi/4.7.3/thumb/cortex-m0
    freescale_arm
    ../../sat/arm-none-eabi/include
    ../../sat/arm-none-eabi/include/sys/
    ../../sat/lib/
    ../../sat/lib/gcc/arm-none-eabi/4.6.2/plugin/include/c
    '''))
    #../../Freescale/MCU/ARM_GCC_Support/ewl/lib/armv6-m/
    #../../Freescale/Cross_Tools/arm-none-eabi-gcc-4_6_2/lib/gcc/arm-none-eabi/4.6.2/armv6-m/
    #../../sat/arm-none-eabi/lib/thumb/cortex-m0/
    #objects
    
ObjectList = env.StaticObject(source = SourceList) #Compile our source files into a buch of object file. Yet to be linked.

env.Program(target = 'neon.elf', source = ObjectList) # Link our program together into an elf file. Uses the following command: $LINK $LINK $SOURCES $__RPATH $_LIBDIRFLAGS $_LIBFLAGS $LINKFLAGS -o $TARGET


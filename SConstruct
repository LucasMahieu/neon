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
    freescale_source/__arm_eabi_init.c
    freescale_source/gcc_ctor_dtor.c
    freescale_source/ROMCopy.c
    ''') #Define list of file to compile

env = DefaultEnvironment(Split('''
    tools = ['gcc', 'gnulink']
    CC = '/home/bklippenstein/sat/bin/arm-none-eabi-gcc'
    PROGSUFFIX = 'elf'
    LINK = '/home/bklippenstein/sat/bin/arm-none-eabi-ld'
    LINKCOM ='$LINK $SOURCES $__RPATH $_LIBDIRFLAGS $_LIBFLAGS $LINKFLAGS -o $TARGET'
    '''))
    # Set up default environment to use our cross compiler and output an elf file. Also adjust the linker command order.

env = DefaultEnvironment()
env['CC'] = '/home/bklippenstein/sat/bin/arm-none-eabi-gcc'
env['PROGSUFFIX'] = 'elf'
env['LINK'] = '/home/bklippenstein/sat/bin/arm-none-eabi-ld'
env['LINKCOM'] ='$LINK $SOURCES $__RPATH $_LIBDIRFLAGS $_LIBFLAGS $LINKFLAGS -o $TARGET'


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
    ./include
    ./freescale_source
    ./freescale_include
    /home/bklippenstein/sat/arm-none-eabi/include
    /home/bklippenstein/sat/arm-none-eabi/include/sys/
    /home/bklippenstein/sat/lib/
    /home/bklippenstein/sat/lib/gcc/arm-none-eabi/4.6.2/plugin/include/c
    ''')) #Set include directories for GCC
    
env.Append(LINKFLAGS = Split('''
    -nostartfiles
    -nostdlib
    --gc-sections
    --start-group
    -lc
    --end-group
    -Map neon.map
    -n
    -Tsource/MKL25Z128_flash.ld
    ''')) #Set linker flags to use.
    #    -nodefaultlibs
    

env.Append(LIBPATH = [Split('''
    /home/bklippenstein/work/neon/freescale_arm
    /home/bklippenstein/sat/arm-none-eabi/include
    /home/bklippenstein/sat/arm-none-eabi/include/sys/
    /home/bklippenstein/sat/lib/
    /home/bklippenstein/sat/lib/gcc/arm-none-eabi/4.6.2/plugin/include/c
    ''')])
    
ObjectList = env.StaticObject(source = SourceList) #Compile our source files into a buch of object file. Yet to be linked.

env.Program(target = 'neon.elf', source = ObjectList) # Link our program together into an elf file. Uses the following command: $LINK $LINK $SOURCES $__RPATH $_LIBDIRFLAGS $_LIBFLAGS $LINKFLAGS -o $TARGET


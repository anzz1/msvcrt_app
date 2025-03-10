# msvcrt_app

Even though [Raymond does not like it](https://devblogs.microsoft.com/oldnewthing/20140411-00/?p=1273), sometimes you just want to link against msvcrt.dll which ships by default on Windows since 2000 so you can use a standard set of standard library functions without depending on anything, and also skipping the heavy CRT startup and insertion of stack canaries in your functions that modern MSVC wants to do today.  
MinGW also links against msvcrt, which is stable and battle-tested. That is how executables compiled with MinGW are usually smaller and faster than ones compiled with MSVC, but now MSVC can (once again) do it too, and free you from the shackles of UCRT.

The repository includes msvcrt.lib for linking against msvcrt.dll, and preconfigured Visual Studio (2017) blank project files to use it, plus a CRT startup stub.

The msvcrt.lib was created using these commands
```bat
dumpbin.exe /EXPORTS C:\Windows\System32\msvcrt.dll > x64/msvcrt.exports
echo EXPORTS > ./Win32/msvcrt.def
sed -r "s/.*?(:?[A-F0-9]+ ){2}/\t/;tx;d;:x" ./Win32/msvcrt.exports >> ./Win32/msvcrt.def
lib.exe /MACHINE:X86 /def:Win32/msvcrt.def /out:Win32/msvcrt.lib

dumpbin.exe /EXPORTS C:\Windows\System32\msvcrt.dll > x64/msvcrt.exports
echo EXPORTS > ./x64/msvcrt.def
sed -r "s/.*?(:?[A-F0-9]+ ){2}/\t/;tx;d;:x" ./x64/msvcrt.exports >> ./x64/msvcrt.def
lib.exe /MACHINE:X64 /def:x64/msvcrt.def /out:x64/msvcrt.lib

copy x64/msvcrt.def ARM64/msvcrt.def
echo _fpieee_flt >> ARM64/msvcrt.def
echo _memcpy_strict_align >> ARM64/msvcrt.def
echo fabsf >> ARM64/msvcrt.def
lib.exe /MACHINE:ARM64 /def:ARM64/msvcrt.def /out:ARM64/msvcrt.lib
```

A GitHub Action to generate those libraries can be found [here](https://github.com/namazso/msvcrt.lib).

# Design Documents
The decompress library does not depend on other jaids libraries and works independently. As of Ver1.0.0, only the static library version has been released.

## How to build

This tool uses CMake to build.

```
$git clone https://github.com/jai-rd/lossless_compression
$cd lossless_compression
$build>cmake -S . -B build -D BUILD_SHARED_LIBS=ON
$lossless_compression>cd build
```
After that, you should build correspond to your environment.
## Windows Environment
You can find lossless.sln in the build folder and open "lossless.sln" from VisualStudio and build libloessless.
After build procedure, you can find library files in the build\modules folder.
## Linux Environment
You execute make in the build directory. After building, you can find libliblossless.so in the build/modules directory.

## Folder Structure

```
Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
d-----        2022/04/01     11:38                .github
d-----        2022/04/27     17:13                docs
d-----        2022/04/05     19:29                include
d-----        2022/04/05     19:29                src
d-----        2022/04/01     11:38                test
d-----        2022/04/05     19:29                test_app
```

| folder   |                                |
| -------- | ------------------------------ |
| docs     | Design documents         |
| include  | Public Header files           |
| src      | src code                       |
| test     | test code using Google Test |
| test_app | Example of decompressing a decompressed image into a PvBuffer  |

## OSS in Use

| OSS name   | Version | Url                                    |
| ---------- | ------- | -------------------------------------- |
| ThreadPool |         | https://github.com/progschj/ThreadPool |

* ThreadPool is a Zlib license, and it is free to use. It does not require any notation in the application.

## Modular Design

​	[Module Configuration](design.md)


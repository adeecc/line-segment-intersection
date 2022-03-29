# SweepLine Algorithm for Line Segment Intersection

## Team (Group 9)

| Name                                                        |   ID Number   |
| :---------------------------------------------------------- | :-----------: |
| [Aditya Chopra](https://github.com/adeecc)                  | 2019A7PS0178H |
| [Omkar Pitale](https://github.com/CyberKnight1803)          | 2019A7PS0083H |
| [Vedansh Srivastava](https://github.com/vedansh-srivastava) | 2019A7PS0323H |

## Instructions

### Run the Demonstrations

```sh
bash run.sh
```

### Run the Tests

```sh
bash test.sh
```

## Custom Build Instructions

1. Generate Build Files

```sh
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -H. -B./build -G "Unix Makefiles"
```

2. Build all targets

### Building in Release Mode.

```sh
cmake --build ./build --config Relase --target all
```

### Building in Debug Mode

```sh
cmake --build ./build --config Debug --target all -j 10 --
```

> You need to compile atleast the `crusty_compiler` static library, and `app` to run the demo executable
> Easist way to get tests to work is to build all targets. We use gtest for testing, which has several targets that are required and it can get messy installing them.

3. Running the Demo Parser

> Assuming the Current Working Directory is `./bin`

```sh
chmod +x ./app
./app
```

4. Running the Tests

> Assuming the Current Working Directory is `./bin/tests`

```sh
chmod +x ./lexer_tests
./lexer_tests
```

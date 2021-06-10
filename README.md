### audience_exercise

#### Setup
To run the program, you have to download and install GoogleTest on your system. To do this just follow the steps from official gtest repository ([GoogleTest](https://github.com/google/googletest/tree/master/googletest)).
After that make sure that gtest has been installed in /usr/local/lib/ directory. Otherwise there is need to change manually the path inside Makefile.  

When GoogleTest is configured in the main directory run 

```
make
```

It will create two exe files in build directory AudienceExercise for application and AudienceExerciseTest for tests.
The output file from running application will be inside resources directory.



# Raytra
A OpenEXR renderer for scn files. Made for COMS4160 Fall 17' class, Columbia University. Test files are in __test__ directory.

# Compile & Build
run the following command:
g++ -O2 *.cc -std=c++11 -I. -I/usr/include/OpenEXR -lIlmImf -lImath -lHalf -Wall -o raytra

# Run the program
run the following command (format: input *.scn, output *.exr):
./raytra <input_file_name> <output_file_name>

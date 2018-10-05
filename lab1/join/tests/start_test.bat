echo 1. input_base.txt input_space.txt>test_output.txt
join.exe test_output.txt input_base.txt input_space.txt temp1.txt
join.exe temp1.txt test_output.txt
echo:>temp1.txt
join.exe test_output.txt temp1.txt temp2.txt
join.exe temp2.txt test_output.txt

echo 2. input_base.txt input_endl.txt>temp2.txt
join.exe temp2.txt input_base.txt input_endl.txt temp1.txt
join.exe test_output.txt temp1.txt temp2.txt
join.exe temp2.txt test_output.txt
echo:>temp1.txt
join.exe test_output.txt temp1.txt temp2.txt
join.exe temp2.txt test_output.txt

echo 3. input_custom.txt input_custom.txt>temp2.txt
join.exe temp2.txt input_custom.txt input_custom.txt temp1.txt
join.exe test_output.txt temp1.txt temp2.txt
join.exe temp2.txt test_output.txt
echo:>temp1.txt
join.exe test_output.txt temp1.txt temp2.txt
join.exe temp2.txt test_output.txt

echo 4. input_custom.txt input_that_not_actually_existing.txt>temp2.txt
join.exe test_output.txt temp2.txt temp1.txt
join.exe temp1.txt test_output.txt
join.exe input_custom.txt input_that_not_actually_existing.txt temp2.txt>temp1.txt
join.exe test_output.txt temp1.txt temp2.txt
join.exe temp2.txt test_output.txt

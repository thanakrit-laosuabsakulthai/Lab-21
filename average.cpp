#include <iostream>
#include <cstdlib>

int main(int argument_count, char* argument_values[]) {
	if (argument_count > 1) {
		double sum = 0.0;
		for (int i = 1; i < argument_count; ++i) {
			sum += std::atof(argument_values[i]);
		}
		
		double average = sum / (argument_count - 1);
		std::cout << "---------------------------------" << std::endl;
		std::cout << "Average of " << (argument_count - 1) << " numbers = " << average << std::endl;
		std::cout << "---------------------------------" << std::endl;
	} else {
		std::cout << "Please input numbers to find average." << std::endl;
	}
	
	
	return 0;
}
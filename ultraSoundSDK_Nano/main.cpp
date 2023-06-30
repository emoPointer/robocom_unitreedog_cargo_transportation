#include "UltraSound_UART.h"
#include <iostream>
#include <unistd.h>

// int main(){
//     UltraSound ul1(1);
//     UltraSound ul2(2);
//     UltraSound ul3(3);
//     double dis;

//     while(true){
//         if(ul1.measureDistance(dis)){
//             std::cout << "ul1 Distance: " << dis << std::endl;
//         }
//         if(ul2.measureDistance(dis)){
//             std::cout << "ul2 Distance: " << dis << std::endl;
//         }
//         if(ul3.measureDistance(dis)){
//             std::cout << "ul3 Distance: " << dis << std::endl;
//         }
//         usleep(500000);
//     }
// }

int main(){
	if(true){
	    std::vector<uint8_t> ids;
	    ids.push_back(0);
	    //ids.push_back(2);
	    //ids.push_back(3);

	    UltraSoundGroup ug(ids);

	    std::vector<double> distance;

	    long long time;

	    while(true){
	    time = getSystemTime();
	    distance = ug.getDistance();
	    std::cout << "cost time: " << getSystemTime() - time << std::endl;

	    for(int i(0); i<distance.size(); ++i){
		std::cout << distance[i] << "   ";
	    }
	    std::cout << std::endl;
	    }
	}

	else{
	     UltraSound ul1(1);
	     UltraSound ul2(2);
	     UltraSound ul3(3);
	     double dis;

	     while(true){
		 if(ul1.measureDistance(dis)){
		     std::cout << "ul1 Distance: " << dis << std::endl;
		 }
		 if(ul2.measureDistance(dis)){
		     std::cout << "ul2 Distance: " << dis << std::endl;
		 }
		 if(ul3.measureDistance(dis)){
		     std::cout << "ul3 Distance: " << dis << std::endl;
		 }
		 usleep(500000);
	     }
	}
}

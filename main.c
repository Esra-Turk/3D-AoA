#include<stdio.h>
#include<math.h>
#include<stdlib.h>

struct AnchorParams {
    int tag;
    double distance;
    double x;
    double y;
    double z;
};

struct AnchorParams anchorParams[6];

int packetReceived[6] = {0}; // Her anchor için bir takipci.

// İki nokta arasındaki öklidyen uzaklığı hesaplayan fonksiyon
double distance(double point1[3], double point2[3]) {
    return sqrt(pow(point1[0] - point2[0], 2) + pow(point1[1] - point2[1], 2) + pow(point1[2] - point2[2], 2));
}

double calculateR(double a, double b, double c){
    return sqrt((2 * a * a + 2 * b * b - c * c) / 4);
}

int allPacketsReceived() {
    for (int i = 0; i < 6; i++) {
        if (packetReceived[i] == 0) {
            return 0; // En az bir paket alinmamis.
        }
    }
    return 1; // Tüm paketler alinmis.
}


int checkTriangle(double a, double b, double c) {
    if (a > 0 && b > 0 && c > 0 && a + b > c && a + c > b && b + c > a)
        return 1; // Ucgen olusturulabilir
    else
        return 0; // Ucgen olusturulamaz
}

void aOa3D(int anchor_tag, double x, double y, double z){ 
	double mobileNode[3] = {20, 20, 37};
    double anchorPoint[3] = {x, y, z};
	double optimalDistance = 20;
	double theta, sigma;

	anchorParams[anchor_tag - 1].tag = anchor_tag;
    anchorParams[anchor_tag - 1].x = x;
    anchorParams[anchor_tag - 1].y = y;
    anchorParams[anchor_tag - 1].z = z;

	if(anchor_tag == 1 || anchor_tag == 2){
        mobileNode[2] = 0;
        anchorParams[anchor_tag - 1].distance = distance(mobileNode, anchorPoint);
    } else {
        anchorParams[anchor_tag - 1].distance = distance(mobileNode, anchorPoint);
    }
	
	packetReceived[anchor_tag - 1] = 1; // Paket alindi olarak isaretler
	printf("Anchor_%d sended a loc. packet\n", anchor_tag);

	if (allPacketsReceived()) {
		double distance1 = anchorParams[0].distance;
		double distance2 = anchorParams[1].distance;
		double distance3 = anchorParams[2].distance;
		double distance4 = anchorParams[3].distance;
		double distance5 = anchorParams[4].distance;
		double distance6 = anchorParams[5].distance;

		printf("distance1: %f\ndistance2: %f\ndistance3: %f\ndistance4: %f\ndistance5: %f\ndistance6: %f\n", distance1, distance2, distance3, distance4, distance5, distance6);
		
		int isTriangle2D = checkTriangle(distance1, distance2, optimalDistance);
		int isTriangle3D = checkTriangle(distance3, distance4, optimalDistance);

		if(isTriangle2D && isTriangle3D){
	        // r2 -> 3D median length
            double r2 = calculateR(distance3, distance4, optimalDistance);
           
            if (distance6 > distance5) {
                theta = acos((r2 * r2 + (optimalDistance/2) * (optimalDistance/2) - distance3 * distance3) / (2 * r2 * (optimalDistance/2))) * (180.0 / M_PI);
            } else {
                theta = 360 - acos((r2 * r2 + (optimalDistance/2) * (optimalDistance/2) - distance3 * distance3) / (2 * r2 * (optimalDistance/2))) * (180.0 / M_PI);
            }

            printf("3D Triangle: r2 = %f, theta = %f\n", r2, theta);

            // r1 -> 2D median length
    		double r1 = calculateR(distance1, distance2, optimalDistance);
           
            if (distance6 > distance5) {
                sigma = acos((r1 * r1 + (optimalDistance/2) * (optimalDistance/2) - distance1 * distance1) / (2 * r1 * (optimalDistance/2))) * (180.0 / M_PI);
            } else {
                sigma = 360 - acos((r1 * r1 + (optimalDistance/2) * (optimalDistance/2) - distance1 * distance1) / (2 * r1 * (optimalDistance/2))) * (180.0 / M_PI);
            }

           printf("2D Triangle: r1 = %f, sigma = %f izdüşüm r2 = %f\n ", r1, sigma, r2 * cos((90 - theta) * M_PI / 180.0));
		} else {
			printf("These lengths cannot form a triangle.\n");
		}

    }

}
int main( void )
{
    aOa3D(1, 10, 0, 0); // Anchor_1_Call
    aOa3D(2, -10, 0, 0); // Anchor_2_Call
    aOa3D(3, 0, 0, 10); // Anchor_3_Call
    aOa3D(4, 0, 0, -10); // Anchor_4_Call
    aOa3D(5, 0, 10, 0); // Anchor_5_Call
    aOa3D(6, 0, -10, 0); // Anchor_6_Call
	return 0;
}
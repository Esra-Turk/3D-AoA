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

struct AnchorParams anchorParams[4];

// Fonksiyonun kac kez cagrildigini sayar
int callCount = 0;

int checkTriangle(double a, double b, double c) {
    if (a > 0 && b > 0 && c > 0 && a + b > c && a + c > b && b + c > a)
        return 1; // Ucgen olusturulabilir
    else
        return 0; // Ucgen olusturulamaz
}

void aOa3D(int anchor_tag, double distance, double x, double y, double z){ 
	double optimalDistance = 20;

	anchorParams[anchor_tag - 1].tag = anchor_tag;
    anchorParams[anchor_tag - 1].distance = distance;
    anchorParams[anchor_tag - 1].x = x;
    anchorParams[anchor_tag - 1].y = y;
    anchorParams[anchor_tag - 1].z = z;

	callCount++;

	if (callCount == 4) {
		double distance1 = anchorParams[0].distance;
		double distance2 = anchorParams[1].distance;
		double distance3 = anchorParams[2].distance;
		double distance4 = anchorParams[3].distance;
		
		int isTriangle2D = checkTriangle(distance1, distance2, optimalDistance);
		int isTriangle3D = checkTriangle(distance3, distance4, optimalDistance);

		if(isTriangle2D){
			// r1 -> 2D median length
			double r1 = sqrt((2 * distance1 * distance1 + 2 * distance2 * distance2 - optimalDistance * optimalDistance) / 4);
			double theta = acos((r1 * r1 + optimalDistance/2 * optimalDistance/2 - distance2 * distance2) / (2 * r1 * optimalDistance/2))* (180.0 / M_PI);
			printf("2D Triangle: r1 = %f, theta = %f\n", r1, theta);
		} else {
			printf("These lengths cannot form a triangle.\n");
		}
		
		if(isTriangle3D) {
			//r2 -> 3D median length
			double r2 = sqrt((2 * distance3 * distance3 + 2 * distance4 * distance4 - optimalDistance * optimalDistance) / 4);
			double sigma = acos((r2 * r2 + optimalDistance/2 * optimalDistance/2 - distance3 * distance3) / (2 * r2 * optimalDistance/2)) * (180.0 / M_PI);
			printf("3D Triangle: r2 = %f, sigma = %f\n", r2, sigma);
		} else {
			printf("These lengths cannot form a triangle.\n");
		}

    }

}
int main( void )
{
	aOa3D(1, 9.0000, -10, 0, 0); //Anchor_1_Call
	printf("Anchor_1 sended a loc. packet\n");
	aOa3D(2, 5.0000, 10, 0, 0); //Anchor_2_Call
	printf("Anchor_2 sended a loc. packet");
	aOa3D(3, 10.0000, 0, 0, 10); //Anchor_3_Call
	printf("Anchor_3 sended a loc. packet");
	aOa3D(4, 10.0000, 0, 0, 10); //Anchor_4_Call
	printf("Anchor_4 sended a loc. packet");
	return 0;
}
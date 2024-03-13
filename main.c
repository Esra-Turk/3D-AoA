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

struct AnchorParams anchorParams[2];

// Fonksiyonun kaç kez çağrıldığını sayar
int callCount = 0;

void aOa3D(int anchor_tag, double distance, double x, double y, double z){ 
	double optimalDistance = 20;

	anchorParams[anchor_tag - 1].tag = anchor_tag;
    anchorParams[anchor_tag - 1].distance = distance;
    anchorParams[anchor_tag - 1].x = x;
    anchorParams[anchor_tag - 1].y = y;
    anchorParams[anchor_tag - 1].z = z;

	callCount++;

	if (callCount == 2) {
		double distance1 = anchorParams[0].distance;
		double distance2 = anchorParams[1].distance;
		
		// r1 -> median length
		double r1 = sqrt((2 * distance1 * distance1 + 2 * distance2 * distance2 - optimalDistance * optimalDistance) / 4);
		
		double theta = acos((r1 * r1 + optimalDistance/2 * optimalDistance/2 - distance2 * distance2) / (2 * r1 * optimalDistance/2));
    	theta = theta * (180.0 / M_PI);
		
		printf("%f\n", r1);
		printf("%f\n", theta);
        
    }

}
int main( void )
{
	aOa3D(1, 16.0000, -10, 0, 0); //Anchor_1_Call
	printf("Anchor_1 sended a loc. packet\n");
	aOa3D(2, 13.0000, 10, 0, 0); //Anchor_2_Call
	printf("Anchor_2 sended a loc. packet");
	/*aOa-3D(3, distance3, anchor3_x, anchor3_y, anchor3_z); //Anchor_3_Call
	printf("Anchor_3 sended a loc. packet");
	aOa-3D(4, distance4, anchor4_x, anchor4_y, anchor4_z); //Anchor_4_Call
	printf("Anchor_4 sended a loc. packet");*/
	return 0;
}
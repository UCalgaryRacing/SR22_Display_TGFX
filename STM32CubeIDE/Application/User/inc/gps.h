/*
 * gps.h
 *
 *  Created on: 19 Jul 2023
 *      Author: Me
 */

#ifndef APPLICATION_USER_INC_GPS_H_
#define APPLICATION_USER_INC_GPS_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "math.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

typedef struct{
    double x;
    double y;
}Point;

typedef struct{
	Point start;
	Point end;
}Line;
/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
double MaxDouble(double x, double y);
double MinDouble(double x, double y);
bool OnSegment(Point p, Point q, Point r);
uint8_t Orientation(Point p, Point q, Point r);
bool DoIntersect(Point p1, Point q1, Point p2, Point q2);


/* USER CODE END Prototypes */



#endif /* APPLICATION_USER_INC_GPS_H_ */

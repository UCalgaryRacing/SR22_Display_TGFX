/*
 * gps.c
 *
 *  Created on: 19 Jul 2023
 *      Author: Me
 */

/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    gps.c
 * @brief   This file provides code for the configuration
 *          of the RPM instances.
 ******************************************************************************
 * @attention
 *
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include <gps.h>

/* Defines*/

/* Variables */

/* Functions */
double MaxDouble(double x, double y){
    return x > y ? x : y;
}

double MinDouble(double x, double y){
    return x < y ? x : y;
}

bool OnSegment(Point p, Point q, Point r){
    if(
        q.x <= MaxDouble(p.x, r.x) &&
        q.x >= MinDouble(p.x, r.x) &&
        q.y <= MaxDouble(p.y, r.y) &&
        q.y >= MinDouble(p.y, r.y)
    ){
        return true;
    }
    return false;
}

uint8_t Orientation(Point p, Point q, Point r){
    double value = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if(value == 0){
        return 0;
    }
    return value > 0 ? 1 : 2;
}

bool DoIntersect(Point p1, Point q1, Point p2, Point q2){
    uint8_t o1 = Orientation(p1, q1, p2);
    uint8_t o2 = Orientation(p1, q1, q2);
    uint8_t o3 = Orientation(p2, q2, p1);
    uint8_t o4 = Orientation(p2, q2, q1);

    if(o1 != o2 && o2 != o4){
        return true;
    }

    if(o1 == 0 && OnSegment(p1, p2, q1)){
        return true;
    }

    if (o2 == 0 && OnSegment(p1, q2, q1)){
       return true;
    }

    if (o3 == 0 && OnSegment(p2, p1, q2)){
        return true;
    }

    if (o4 == 0 && OnSegment(p2, q1, q2)){
        return true;
    }

    return false;
}




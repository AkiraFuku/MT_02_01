#pragma once
#include <KamataEngine.h>
#include "MassFunction.h"
#include <Novice.h>
using namespace KamataEngine;
struct Sphere{
	Vector3 center;//中心
	float radius;
};
struct Line{
	Vector3 origin;//起点
	Vector3 diff;//方向

};
struct Ray{
	Vector3 origin;//起点
	Vector3 diff;//方向
};
struct  Segment{
	Vector3 origin;//起点
	Vector3 diff;//方向
};

void DrawSphere(
	const Sphere& sphere,
	const Matrix4x4& viewProjectionMatrix,
	const Matrix4x4& viewportMatrix,
	uint32_t color
	
);
void DrawGrid(
	const Matrix4x4& viewProjectionMatrix,
	const Matrix4x4& viewportMatrix
);
Vector3 Project(const Vector3& v1,const Vector3& v2);
Vector3 ClosestPoint(const Vector3& point,const Segment& segment);

bool IsCollision(const Sphere& si,const Sphere& s2);

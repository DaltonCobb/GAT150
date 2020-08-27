#include "pch.h"
#include "Transform.h"
#include <string>

namespace nc 
{
std::istream& nc::operator >> (std::istream& stream, Transform& transform)
{
	stream >> transform.position;

	std::string line;
	std::getline(stream, line);
	transform.scale = stof(line);

	std::getline(stream, line);
	transform.angle = stof(line);

	return stream;
}

void Transform::Update()
{
	Matrix33 mxs;
	mxs.Scale(scale);

	Matrix33 mxr;
	mxr.Rotate(angle);

	Matrix33 mxt;
	mxt.Translate(position);

	matrix = mxs * mxr * mxt;
}

void Transform::Update(const Matrix33& mx)
{
	Matrix33 mxs;
	mxs.Scale(scale);

	Matrix33 mxr;
	mxr.Rotate(angle);

	Matrix33 mxt;
	mxt.Translate(position);

	matrix = mxs * mxr * mxt * mx;
}

}

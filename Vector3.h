#ifndef VECTOR3_H_
#define VECTOR3_H_

typedef struct Vector3
{
	float x;
	float y;
	float z;

	Vector3() = default;
	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	/*-----　演算子オーバーロード　-----*/

	Vector3 operator + (const Vector3 add_v3) const
	{
		Vector3 v3;

		v3.x = this->x + add_v3.x;
		v3.y = this->y + add_v3.y;
		v3.z = this->z + add_v3.z;

		return v3;
	}

	Vector3 operator - (const Vector3 minus_v3) const
	{
		Vector3 v3;

		v3.x = this->x - minus_v3.x;
		v3.y = this->y - minus_v3.y;
		v3.z = this->z - minus_v3.z;

		return v3;
	}

	Vector3 operator * (float multiply_num) const
	{
		Vector3 v3;

		v3.x = this->x * multiply_num;
		v3.y = this->y * multiply_num;
		v3.z = this->z * multiply_num;

		return v3;
	}

	Vector3 operator / (float divide_num) const
	{
		Vector3 v3;

		if (divide_num == 0.0f)
			return *this;

		v3.x = this->x / divide_num;
		v3.y = this->y / divide_num;
		v3.z = this->z / divide_num;

		return v3;
	}

	Vector3& operator += (const Vector3 add_v3)
	{
		this->x += add_v3.x;
		this->y += add_v3.y;
		this->z += add_v3.z;

		return *this;
	}

	Vector3& operator -= (const Vector3 minus_v3) 
	{
		this->x -= minus_v3.x;
		this->y -= minus_v3.y;
		this->z -= minus_v3.z;

		return *this;
	}

	Vector3& operator *= (float multiply_num) 
	{
		this->x *= multiply_num;
		this->y *= multiply_num;
		this->z *= multiply_num;

		return *this;
	}

	Vector3& operator /= (float divide_num) 
	{
		if (divide_num == 0.0f)
			return *this;

		this->x /= divide_num;
		this->y /= divide_num;
		this->z /= divide_num;

		return *this;
	}

	Vector3& operator = (float change_num) 
	{
		this->x = change_num;
		this->y = change_num;
		this->z = change_num;

		return *this;
	}

	bool operator == (const Vector3& v3_other)
	{
		if (this->x != v3_other.x) return false;
		if (this->y != v3_other.y) return false;
		if (this->z != v3_other.z) return false;
		return true;
	}

	bool operator != (const Vector3& v3_other)
	{
		if (this->x == v3_other.x) return false;
		if (this->y == v3_other.y) return false;
		if (this->z == v3_other.z) return false;
		return true;
	}

	/*----------------------*/

	// Vector3からdxlibのVECTORへの変換
	VECTOR Vec3ToVec(Vector3 v3)
	{
		VECTOR Result;
		Result.x = v3.x;
		Result.y = v3.y;
		Result.z = v3.z;
		return Result;
	}

};


#endif
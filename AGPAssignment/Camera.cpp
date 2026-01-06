#include "Camera.h"
DirectX::XMMATRIX Camera::GetViewMatrix()
{
	DirectX::XMVECTOR eyePos = transform.position;
	DirectX::XMVECTOR lookAt = transform.GetForward();
	DirectX::XMVECTOR camUp = transform.GetUp();

	
	return DirectX::XMMatrixLookToLH(eyePos, lookAt, camUp); // looks foward (at the object)
}

DirectX::XMMATRIX Camera::GetProjectionMatrix(int screenWidth, int screenHeight)
{
	return DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(fov), 
		screenWidth / (float)screenHeight, 
		nearClippingPlane, 
		farClippingPlane);

	// look into XMMatrixOrthographicLH for ortho view
}
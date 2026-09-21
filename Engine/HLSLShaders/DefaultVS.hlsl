float4 main( float3 pos : POSITION ) : SV_POSITION
{
	return float4(pos, 1);
}

/*
 * 입력이 어떻게 생겼는지 따로 알려줘야한다. DirectX에서는 이를 Input Layout이라 말함
 * POSITION이 세멘틱에 해당하는데, 
 */
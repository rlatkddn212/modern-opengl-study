## OpenGL 정리 문서



OpenGL 슈퍼바이블 6판 내용을 참고하여 정리합니다.

책 내용을 기반으로 정리하지만 인터넷에서 여러 자료들을 찾아가면서 이해가 잘 안되거나, 부족한 내용을 체워볼까 합니다. :)

OpenGL 슈퍼 바이블의 경우 자체 lib을 만들어 구현하는데요. 이런 방법보다 OpenGL에서 자주사용되는 lib GLFW, GLM을 사용합니다.

책에서 제공하는 코드랑 전혀 별개로 구현됩니다.  

---------------------
### 코드는 어떻게 보나요?
OpenGL_Project 폴더에 있습니다.

-----------------------
### 사용하는 오픈지엘 라이브러리

GLFW, GLM, GLEW, stb_image 입니다.

-----------------------
### 프로젝트 구성
| 챕터 | 문서 링크 | 프로젝트 |
|----------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-|
| 01. 소개 | [[문서]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/01.%20소개/README.md)                                 | 없음 |
| 02. 나의 첫 번째 OpenGL 프로그램 |[[문서]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/02.%20나의%20첫%20번째%20OpenGL%20프로그램/README.md) | [[첫번째 프로젝트]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C02_FirstProgram) |
| 03. 파이프라인 따라가기 |[[문서]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/03.%20파이프라인%20따라가기/README.md) | [[3D데이터 이동처리 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C03_DataTransfer) [[테셀레이션 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C03_Tessellation) |
| 04. 3D 그래픽스를 위한 수학 | [[문서]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/04.%203D%20그래픽스를%20위한%20수학/README.md) | [[베지어 곡선 그리기]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C04_Line) [[GLM 행렬 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C04_Matrix) [[GLM 벡터 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C04_Vector) |
| 05. 데이터 | [[문서]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/05.%20데이터/README.md)                               |[[OpenGL 버퍼예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C05_Buffer) [[쉐이더 속성값 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C05_Attrib)[[유니폼 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C05_Uniform)[[유니폼 블록 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C05_UniformBlock)[[Map 버퍼 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C05_MapBuffer) [[텍스쳐 로드 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C05_TextureLoading) [[텍스쳐 래핑 모드 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C05_TextureWrapping)  [[텍스쳐 필터링 모드 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C05_TextureFiltering)  [[텍스쳐 샘플러 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C05_TextureSampling)  [[멀티 텍스쳐 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C05_MultiTexture)  [[텍스쳐 밉맵 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C05_TextureMipmap) [[배열 텍스쳐 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C05_ArrayTexture) |
| 06. 쉐이더와 프로그램 |  [[문서]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/06.%20쉐이더와%20프로그램/README.md) |  |
| 07. 버텍스 프로세싱 및 드로잉 커맨드 | [[문서]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/07.%20버텍스%20프로세싱%20및%20드로잉%20커맨드/README.md) |  [[인덱스된 모델 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C07_DrawIndexedModel)[[인스턴스 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C07_InstancedModel)[[변환 피드백 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C07_TransformFeedBack)[[사용자 정의 클리핑 예제]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/OpenGL_Project/C07_ClipDistance)|
| 08. 프리미티브 프로세싱 | [[문서]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/08.%20프리미티브%20프로세싱/README.md) |  |
| 09. 프래그먼트 프로세싱 및 프래임 버퍼 |[[문서]](https://github.com/rlatkddn212/opengl_super_bible/tree/master/09.%20프래그먼트%20프로세싱%20및%20프래임%20버퍼/README.md)  |  |
| 10. 컴퓨트 쉐이더 |  |  |
| 11. 파이프라인 제어 및 모니터링 |  |  |
| 12. 랜더링 테크닉 |  | TODO : 디퍼드 쉐이딩, |
| 13. 디버깅 및 성능 최적화 |  |  |
| 14. 플랫폼 세부사항 |  |  |
|15. 추가로 구현해볼 사항 |  | 그림자 볼륨, ShaderToy, 캐릭터 애니메이션, 카툰쉐이딩  |
|ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ|ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ||

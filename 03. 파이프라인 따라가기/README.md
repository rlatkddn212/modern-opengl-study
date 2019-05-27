## 파이프라인 따라가기



#### 그래픽스 파이프라인

- ![Rendering Pipeline Flowchart](https://www.khronos.org/opengl/wiki_opengl/images/RenderingPipeline.png)





#### 버텍스 쉐이더 데이터 전달





#### 테셀레이션

테셀레이션 컨트롤 쉐이더 -> 고정 함수 테셀레이션 엔진 -> 테셀레이션 이벨류에이션 쉐이더



**테셀레이션 컨트롤 쉐이더** 

- 테셀레이션 엔진에 보낼 테셀레이션의 레벨 결정
- 테셀레이션이 수행된 다음 실해외는 테셀레이션 이벨류에이션에 보낼 데이터 생성



테셀레이션 = 패치

glpatchParameteri를 사용하여 제어점 개수로 하여 호출




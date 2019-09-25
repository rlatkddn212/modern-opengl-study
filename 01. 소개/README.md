# 소개

- 그래픽스 파이프라인
- opengl 역사
- 기본 개념들



## 그래픽스 파이프라인

- 그래픽스 파이프라인 분할을 사용하여 성능을 향상시킬 수 있다.
  - CPU도 명령어 실행 파이프라인을 분할하여 성능을 향상시킨다. 프로그래밍을 할 때도 파이프라인을 나눠서 구현하면 성능향상을 볼 수 있다.
- 추상화 레이어를 통해 어떤 그래픽 카드인지 상관없이 동일한 그래픽스 파이프라인으로 사용가능하다.
- 쉐이더를 이용하여 프로그래밍 가능한 스테이지와 고정 함수(프로그래밍 불가능한) 스테이지로 구분된다.
  - 버텍스 쉐이더, 프래그먼트 쉐이더가 대표적으로 프로그래밍 가능한 스테이지다.

![Rendering Pipeline Flowchart](https://www.khronos.org/opengl/wiki_opengl/images/RenderingPipeline.png)




## OpenGL의 기원과 역사

- 1992년 실리콘 그래픽스 사에서 만든 2, 3차원 표준 API
- 약 250개의 함수 호출을 사용, 모던 opengl은 이 함수들을 직접 사용하지않고 glfw 같은 고수준의 api를 통해 사용된다.
- OpenGL ARB (OpenGL 검수 위원회) 현재는 크로노스 그룹([Khronos Group](https://kr.khronos.org/))
  - 크로노스 그룹은 여러 IT 기업들이 참여하고 있는 그룹이다.



### OpenGL 코어 프로파일

- 구버전 관리가 어려워 호환성 프로파일과, 코어 프로파일로 나눠진다.
- OpenGL은 구버전 호환성을 고려하여 개발되기 때문에 기술적용이 늦어진다.
  - 그래서 불칸이 출시 되었다.



## 프리미티브, 파이프라인, 픽셀

- 프리미티브 : OpenGL 랜더링의 기본 단위
  - 주로 삼각형이다. 점, 선, 삼각형을 랜더링할 수 있다.
  - 볼록 폴리곤이 그리기 쉽기 때문에 오목한 부분이 없는 삼각형 좋다.
- 래스터라이저 : 하드웨어 가속기, 3차원으로 표현된 삼각형을 화면에 그리는 장치
  - <레스터라이저로 만들어진 삼각형>

![img](https://upload.wikimedia.org/wikipedia/commons/b/bc/Rasterisation-triangle_example.svg)

- 레스터라이즈를 자세히 알고 싶다면 아래 사이트를 보는 것이 좋다.
  - <https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation>
  - OpenGL을 시작하기 전 이 사이트부터 보는게 좋을 것 같다.


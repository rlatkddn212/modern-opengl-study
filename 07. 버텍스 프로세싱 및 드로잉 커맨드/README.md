# 버텍스 프로세싱 및 드로잉 커맨드



----------------

### 버텍스 프로세싱



#### 버텍스 쉐이더 입력

- 버텍스 쉐이더 이전 버텍스 관련 입력을 구성해야한다.
- glVertexAttribPointer로 버퍼를 버텍스 쉐이더에 입력으로 연결한다.
- 입력을 넣는 저수준의 함수도 지원한다.



[함수]

- glVertexAtrribFormat
- glVertexAttribBinding
- glBindVertexBuffer



#### 버텍스 쉐이더 출력

- vec4 gl_Position :  변환된 정점의 위치

- float gl_PointSize : 점의 크기

- float gl_ClipDistance[] : 클리핑에 사용됨



----------------

### 드로잉 커맨드



#### 인덱스된 모델 드로잉 커맨드

- glDrawArrays의 경우 인덱스 되지 않은 모델에 대한 드로잉 커맨드이다.
- 인덱스된 모델의 경우 GL_ELEMNET_ARRAY_BUFFER로 인덱스 데이터를 바인딩해야한다.
- 그리고 드로우 커맨드는 glDrawElements를 사용한다.



인덱스 예제 C07_DrawIndexedModel







--------------------

### 변환된 버텍스 저장하기



---------------------

### 클리핑



------------------
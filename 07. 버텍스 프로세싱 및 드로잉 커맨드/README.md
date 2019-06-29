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



#### 베이스 버텍스

- glDrawElementsBaseVertex()



#### 프리미티브 재시작



베이스 버텍스, 프리미티브 재시작 예제 C07_PrimitiveRestart



#### 인스턴스

- glDrawArraysInstanced
- glDrawElementsInstanced



인스턴스 예제 C07_InstancedModel



#### indirect Draw

- Draw 할 때 필요한 인자를 미리 저장해 두거나 인자를 실시간으로 생성하여 변경할 수 있는 방법
- glDrawElements





--------------------

### 변환된 버텍스



#### 변환 피드백



변환 피드백 예제 C07_TransformFeedBack



---------------------

### 클리핑



#### 사용자 정의 클리핑



내장 변수 gl_ClipDistance[]를 사용하여 클립 거리 값을 사용가능



사용자 정의 클리핑 예제 C07_ClipDistance



------------------


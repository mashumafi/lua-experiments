FROM alpine:3.10.2
RUN apk add --no-cache cmake g++ git ninja

WORKDIR /build/
COPY . /workspace/

RUN cmake -GNinja /workspace
RUN cmake --build . --config Debug -- -j10
RUN ctest -j10 -C Debug -T test --output-on-failure
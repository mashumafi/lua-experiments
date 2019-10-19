FROM alpine:3.10.2
RUN apk add --no-cache cmake g++ git ninja

WORKDIR /build

ADD * /workspace/
RUN cmake -GNinja /workspace
RUN ninja
RUN ctest .
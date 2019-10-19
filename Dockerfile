FROM alpine:3.10.2
RUN apk add --no-cache cmake g++ git make

WORKDIR /build

ADD * /workspace/
RUN cmake /workspace
RUN make
RUN make test
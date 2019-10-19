FROM alpine:3.10.2
RUN apk add --no-cache cmake g++ git make

ADD * /workspace/
WORKDIR /workspace

RUN cmake .
RUN make
RUN make test
FROM alpine

RUN apk update && apk upgrade
RUN apk add build-base cmake git ninja linux-headers gdb clang clang-extra-tools

WORKDIR /code

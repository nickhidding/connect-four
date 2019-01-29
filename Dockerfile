# sudo docker build --no-cache -t connect-four .
# sudo docker run --rm --entrypoint cat connect-four /src/ConnectFour > ./dockerConnectFour

FROM ubuntu:18.04
RUN apt-get update && apt-get install -y pkg-config g++ cmake libgtk-3-dev
COPY src/ /src/
RUN cd /src && cmake . && make

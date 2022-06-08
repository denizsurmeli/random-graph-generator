FROM ubuntu:latest


ARG valid_inputs=50
ARG invalid_inputs=0

RUN apt-get update \ 
	&& apt-get install -y git \
												g++ \
												gcc \
												cmake \
												make \
												python3 \
												wget

RUN cd /home && wget https://boostorg.jfrog.io/artifactory/main/release/1.79.0/source/boost_1_79_0.tar.gz&& tar xfz boost_1_79_0.tar.gz \
&& rm boost_1_79_0.tar.gz \
&& cd boost_1_79_0 \
&& ./bootstrap.sh --prefix=/usr/local/ --with-libraries=program_options \
&& ./b2 install \
&& cd /home \
&& rm -rf boost_1_79_0


WORKDIR /src

COPY . rgg

WORKDIR /src/rgg

RUN mkdir -p feeds/in && mkdir -p feeds/out 

WORKDIR /src/rgg/scripts
#generate 10 valid inputs and 0 invalid inputs.Numbers can be modified.
RUN python3 auto_generate.py ${valid_inputs} ${invalid_inputs}

WORKDIR /src/rgg

RUN mkdir build && \
	cd build && \
	cmake .. && \
	cmake --build . && \
	./rgg "../feeds/in"

WORKDIR /src/rgg


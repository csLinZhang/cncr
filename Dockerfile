ARG HOST_ARCH
ARG VERSION

FROM tonglu-docker.pkg.coding.net/tergeo-hub/tergeo-common/${HOST_ARCH}:${VERSION} AS tergeo_depends
ENV MODULE_NAME="simulation"
WORKDIR /home/coding/${MODULE_NAME}
COPY ./ ./
ENV CMAKE_PREFIX_PATH /opt/ros/melodic:${CMAKE_PREFIX_PATH}

RUN sudo apt update && apt install -y libfltk1.3-dev 
RUN ./build_stage.sh
WORKDIR /home/coding/${MODULE_NAME}
RUN /bin/bash -c '. /opt/ros/melodic/setup.bash; ./build.sh'

FROM scratch AS deployer
WORKDIR /install
ENV MODULE_NAME="simulation"
# depends
COPY --from=tergeo_depends /usr/local/ /install/usr/local/
COPY --from=tergeo_depends /usr/lib/x86_64-linux-gnu/libfltk* /install/usr/lib/x86_64-linux-gnu/
COPY --from=tergeo_depends /usr/include/FL/* /install/usr/include/FL/
# stage_simulator
WORKDIR /install/opt/ros/melodic/lib
COPY --from=tergeo_depends /home/coding/simulation/install/lib /install/opt/ros/melodic/lib
WORKDIR /install/opt/ros/melodic/share
COPY --from=tergeo_depends /home/coding/simulation/install/share /install/opt/ros/melodic/share

CMD ["/bin/bash"]
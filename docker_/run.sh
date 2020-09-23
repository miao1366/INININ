#!/bin/bash

#sudo docker build -t buildenv:opencv -f ./Dockerfile.opencv .
#sudo docker run --runtime=nvidia --net=host --privileged --name buildopencv  -v ${PWD}/build_opencv:/tmp/build_opencv -i -t buildenv:opencv /bin/bash

#sudo docker build -t buildenv:cuda10.0-devel-ubuntu18.04 -f ./Dockerfile.cuda10.0-cudnn7-devel-ubuntu18.04 .


#sudo docker run --runtime=nvidia --net=host --privileged --name buildopencv2 -v /dev:/dev  -v ${PWD}/build:/tmp/build -i -t buildenv:cuda10.0-devel-ubuntu18.04 /bin/bash
#sudo docker run --runtime=nvidia --net=host --privileged \
#    --name FMS20190322 -v /dev:/dev  -v /home/senscape/project_run/face.db:/home/senscape/project_run/face.db \
#    -v /home/senscape/project_run/conf.yaml:/home/senscape/project_run/conf.yaml \
#    -v /home/senscape/project_run/slog.config:/home/senscape/project_run/slog.config \
#    -v /home/senscape/project_run/log:/home/senscape/project_run/log -i -t release:FMS20190322 run_fms_master.sh
sudo systemctl enable docker
sudo docker run --runtime=nvidia --net=host --privileged \
    --restart=always \
    --name FMS20190322 -v /dev:/dev \
    -v /home/senscape/project_run/:/home/senscape/project_run/env/  -i -t release:FMS20190322 ./run_fms_master.sh

sudo docker run --runtime=nvidia --net=host --privileged --restart=always --name FMS20190329test -v /dev:/dev -v /home/senscape/project_run/:/home/senscape/project_run/env/  -i -t release:FMS20190329 /bin/bash

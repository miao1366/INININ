# 示例

## 创建Docker镜像
```sh
docker build -t buildenv:v1.0 -f ./Dockerfile.devl .
```

## 查看镜像
```sh
docker images -a
```

## 查看容器
```sh
docker ps -a -q
```
## 运行容器

### 使用主机网络环境、映射/dev:/dev目录、映射临时文件夹
```sh
docker run --runtime=nvidia --net=host --ipc=host --privileged -v /dev:/dev -v ${PWD}/test_dir:/tmp/test_dir --name buildenv_container -i -t buildenv:v1.0 /bin/bash 
```

### 使用nvidia-docker2，--runtime=nvidia
```sh
docker run --runtime=nvidia --rm nvidia/cuda:9.0-base nvidia-smi
```

### 开机启动，--restart=always
```sh
docker run --restart=always ...
systemctl enable docker
```

### 连接到正在运行的容器
```sh
docker exec -it container_id bash
```

### 提交容器为镜像
```sh
docker commit container_id image_name:image_tag
```

## Save
```sh
docker save buildenv:v1.0 | gzip -c > dockerimage.tgz
```

## Load
```sh
gunzip -c dockerimage.tgz | sudo docker load
```

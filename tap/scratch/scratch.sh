
docker stop tapscratch

REM Remove previous container
docker container rm scratch

docker build ../scratch/ --tag tapscratch

docker stop scratch
docker run -p 80:80 tapscratch

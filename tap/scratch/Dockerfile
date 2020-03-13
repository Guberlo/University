FROM httpd:latest

ADD https://tar.goaccess.io/goaccess-1.3.tar.gz  /usr/local/

RUN apt-get update && apt-get install -y goaccess

COPY html/* /usr/local/apache2/htdocs/
COPY conf/* /usr/local/apache2/conf/


CMD ["goaccess", "/usr/local/apache2/access.log", "-o  report.html", "--log-format=COMBINED"]

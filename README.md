# Server

## 1. Developement libraries

    - protobuf >= 2.60
    - leveldb >= 1.18
    - boost >= 1.5
    - cppcms >= 1.0.5
    - libuuid
    - ImageMagick++ (requires libpng on CentOS)
	=> https://www.tecmint.com/install-imagemagick-on-debian-ubuntu/
    - google's sparsehash
    - google's glog
    - cURL with OpenSSL support
    - jwp-cpp
    => https://github.com/Thalhammer/jwt-cpp
        
## 2. Development setup guide for Debian-based environments

    - libprotobuf-dev
    - leveldb-dev
    - uuid-dev
    - libmagick++-dev
    - http://sourcedigit.com/19970-apt-get-command-to-install-imagemagick-7-on-ubuntu-16-04/	
    - libsparsehash-dev
    - libgoogle-glog-dev
    - libssl-dev
    - libcurl4-openssl-dev  
    - https://sourceforge.net/projects/cppcms/files/cppcms/1.0.5/cppcms-1.0.5.tar.bz2/download
    - http://cppcms.com/wikipp/en/page/install_debain_deps
    - http://cppcms.com/wikipp/en/page/cppcms_1x_build	

## 3. Server

    - SSH address: im-server@103.31.126.65
    - Folder: viettalk20
    - Deploy: ./deploy.sh
    - Logs: tail -f logs/vt-server.log
    - Staging server: viettalk@10.84.5.159

## 4. IDE

    - Eclipse : http://www.eclipse.org/downloads/download.php?file=/technology/epp/downloads/release/neon/R/eclipse-cpp-neon-R-linux-gtk-x86_64.tar.gz
    - For more info eclipse 9 on ubuntu : http://askubuntu.com/questions/464755/how-to-install-openjdk-8-on-14-04-lts
    - Plugin xtext : http://download.eclipse.org/modeling/tmf/xtext/updates/composite/releases/
    - Plugin protbuf-dt : http://junit.github.io/protobuf-dt/git/update-site/site.xml
    - Plugin tools (valgrind ...) : http://download.eclipse.org/linuxtools/update

## 5. [CMake Guide]()
## 6. [Guide build push notification library]()

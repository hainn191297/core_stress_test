# BEGIN
# debug script for gdb
# Configuration #1 -b : Build
# Configuration #2 -d : Debug
# Configuration #3 -bd : Build + Debug
# External:
#       -p : build protobuf
# END
set -e

buid_script=server-build.sh
built_exec_full_path=$1 #./build/viettalk-server
remote_exec_full_path=$2 #/opt/server/viettalk-server/viettalk-server
remote_host=$3 #10.84.5.167
remote_gdb_port=$4 #1812
remote_user=$5 #root
remote_pass=$6 #123456a@
running_opt=$7 #arg
exec_file_name=${remote_exec_full_path##*/}
exec_file_path=${remote_exec_full_path%/*}

if [ -z "$1" ]
then 
    printf '%s\n' "Script must start with params."
    printf '\t%s\n' "-b : Build"
    printf '\t%s\n' "-d : Debug"
    printf '\t%s\n' "-bd : Build + Debug"
    printf '\t%s\n' "-p : Build proto"
    exit
fi

# Prioritize protobuf first
if [[ "$*" == *" -p"* ]]
then
    printf '%s\n' ">> Start build protobuf process."
    sh protoc.sh
    printf '%s\n' ">> End protobuf."
	exit
fi

# Prioritize build + debug second
if [[ "$*" == *" -bd"* ]]
then
    printf '%s\n' ">> Start build process."
    sh $buid_script
    printf '%s\n' ">> End build."

    printf '%s\n' ">> Stop $exec_file_name."
    sshpass -p $remote_pass ssh $remote_user@$remote_host "pkill -9 $exec_file_name; pkill -9 gdbserver;" || true
	fuser -k $remote_gdb_port/tcp || true

    printf '%s\n' ">> Copy build to destination."
    sshpass -p $remote_pass scp $built_exec_full_path $remote_user@$remote_host:$remote_exec_full_path
    printf '%s\n' ">> Start debug process."
    sshpass -p $remote_pass nohup ssh -f -L$remote_gdb_port:localhost:$remote_gdb_port $remote_user@$remote_host -N
    sshpass -p $remote_pass ssh $remote_user@$remote_host -t "cd $exec_file_path && gdbserver :$remote_gdb_port $exec_file_name $running_opt"
    fuser -k $remote_gdb_port/tcp
    printf '%s\n' ">> Finish debug."
    exit
fi

if [[ "$*" == *" -bu"* ]]
then
	printf '%s\n' ">> Start build process."
    sh $buid_script
    printf '%s\n' ">> End build."

	printf '%s\n' ">> Stop $exec_file_name."
    sshpass -p $remote_pass ssh $remote_user@$remote_host "pkill -9 $exec_file_name; pkill -9 gdbserver;" || true
	fuser -k $remote_gdb_port/tcp || true

    printf '%s\n' ">> Copy build to destination."
    sshpass -p $remote_pass scp $built_exec_full_path $remote_user@$remote_host:$remote_exec_full_path
	exit
fi

# Last is build/debug
if [[ "$*" == *" -b"* ]]
then
    printf '%s\n' ">> Start build process."
    sh $buid_script
    printf '%s\n' ">> End build."
	exit
fi

if [[ "$*" == *" -d"* ]]
then
    printf '%s\n' ">> Start debug process."
	# pkill -9 gdb || true
    printf '%s\n' ">> Stop $exec_file_name."
    sshpass -p $remote_pass ssh $remote_user@$remote_host "pkill -9 $exec_file_name; pkill -9 gdbserver;" || true
	fuser -k $remote_gdb_port/tcp || true
    printf '%s\n' ">> Start debug process."
    sshpass -p $remote_pass nohup ssh -f -L$remote_gdb_port:localhost:$remote_gdb_port $remote_user@$remote_host -N
    sshpass -p $remote_pass ssh $remote_user@$remote_host -t "cd $exec_file_path && gdbserver :$remote_gdb_port $exec_file_name $running_opt"
    fuser -k $remote_gdb_port/tcp
    printf '%s\n' ">> Finish debug."
	exit
fi
exit

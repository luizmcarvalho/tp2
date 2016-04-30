echo "export N_MAQ=2" >> /etc/profile.d/tp2-rpc.sh
export N_MAQ=2
chmod +x /etc/profile.d/tp2-rpc.sh
make clean
make all

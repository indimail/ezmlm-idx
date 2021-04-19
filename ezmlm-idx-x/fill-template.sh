version=$(cat conf-version)
release=$(cat conf-release)
prefix=$(head -1 conf-prefix)
email=$(cat conf-email)
sed -e "s/@version@/$version/" \
	-e "s/@email@/$email/" \
	-e "s{@prefix@{$prefix{" \
	-e "s/@release@/$release/"

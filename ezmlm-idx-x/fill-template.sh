version=$(sed -e 's/^.*-//' -e q VERSION )
release=$(cat conf-release)
email=$(cat conf-email)
sed -e "s/@version@/$version/" \
	-e "s/@email@/$email/" \
	-e "s/@release@/$release/"

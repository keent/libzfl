#
# Simple script to resolve a pull request
# Contributor must have cloned zfl.git
# Pass contributor name as single argument
#
# Syntax: sh bin/pull.sh contributor branch
#

if [ -z "$1" ]; then
    echo "sh bin/pull.sh contributor branchname"
else
    git checkout -b $2 master
    git pull https://github.com/$1/zfl.git master
    git checkout master
    git merge $2
    git push origin master
    git branch -d $2
fi

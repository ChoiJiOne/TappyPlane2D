@echo off

SET current_date=%date%
SET current_time=%time%
SET commit_message="[DOCS] Update %current_date% %current_time%"

echo START AUTO GIT COMMIT...
git add .
git commit -m %commit_message%
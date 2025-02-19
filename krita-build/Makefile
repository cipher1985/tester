default: android

android:
	docker run -u0 --rm -v ${PWD}/../krita:/home/appimage/krita -v /home/debiansv/cache/artifacts:/home/appimage/artifacts -v /home/debiansv/cache/caches:/home/appimage/caches -w /home/appimage/krita krita-build-android
image:
	docker build -t krita-build-android -f Dockerfile .
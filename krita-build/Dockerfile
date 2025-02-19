FROM invent-registry.kde.org/sysadmin/ci-images/krita-android-builder-sdk34:latest as build

RUN git clone https://invent.kde.org/dkazakov/krita-deps-management.git --depth=1 && \
    git clone https://invent.kde.org/dkazakov/ci-utilities.git krita-deps-management/ci-utilities --depth=1 && \
    git clone https://invent.kde.org/sysadmin/ci-notary-service.git --depth=1 && \
    git clone https://invent.kde.org/sysadmin/ci-utilities.git upstream-ci-utilities --depth=1
    
RUN git config --global --add safe.directory /home/appimage 

FROM invent-registry.kde.org/sysadmin/ci-images/krita-android-builder-sdk34:latest as package

ENV KDECI_BUILD_TYPE=Release \
    KDECI_GITLAB_SERVER=https://invent.kde.org/ \
    KDECI_REPO_METADATA_PATH=/home/appimage/krita-deps-management/repo-metadata \
    KDECI_COMPRESS_PACKAGES_ON_DOWNLOAD=False \
    KDECI_SKIP_ECM_ANDROID_TOOLCHAIN=True \
    CMAKE_TOOLCHAIN_FILE=/home/appimage/krita-deps-management/tools/android-toolchain-krita.cmake \
    KDECI_EXTRA_CMAKE_ARGS="-DHIDE_SAFE_ASSERTS=OFF -DBUILD_TESTING=ON" \
    KDECI_PACKAGE_PROJECT=dkazakov/krita-ci-artifacts-android-arm64-v8a-qt5.15 \
    KRITACI_ANDROID_PACKAGE_TYPE=release \
    KRITACI_SKIP_UPLOAD_NIGHTLY_PACKAGE=True \
    KRITACI_ARCHIVE_ARTIFACTS=True \
    KRITACI_SKIP_COMMON_ARTIFACTS=False \
    KDECI_CC_CACHE=/home/appimage/caches/krita-android/arm64-v8a/ \
    KDECI_CACHE_PATH=/home/appimage/artifacts/krita-android/arm64-v8a/ \
    KDECI_ANDROID_ABI=arm64-v8a \
    DEPS_BRANCH_NAME_ANDROID=master \
    CI_PROJECT_NAME=krita \
    CI_COMMIT_REF_NAME=master

COPY --from=build /home/appimage /home/appimage

CMD bash -c "python3 -u ../krita-deps-management/tools/replace-branch-in-seed-file.py ../krita-deps-management/latest/krita-deps.yml -p -o branch-corrected-deps.yml -d $DEPS_BRANCH_NAME_ANDROID && python3 -u ../krita-deps-management/tools/generate-deps-file.py -s branch-corrected-deps.yml -o .kde-ci.yml && python3 -u ../krita-deps-management/ci-utilities/run-ci-build.py --project $CI_PROJECT_NAME --branch $CI_COMMIT_REF_NAME --platform Android/$KDECI_ANDROID_ABI/Qt5/Shared --only-build --skip-publishing && python3 -u build-tools/ci-scripts/build-android-package.py 2>&1 | tee build-apk.log"
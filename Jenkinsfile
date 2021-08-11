pipeline {
  agent any
  stages {
    stage('检出') {
      steps {
        checkout([$class: 'GitSCM', branches: [[name: env.GIT_BUILD_REF]], 
                            userRemoteConfigs: [[url: env.GIT_REPO_URL, credentialsId: env.CREDENTIALS_ID]]])
      }
    }
    stage('登陆') {
      steps {
        sh 'docker version'
        sh "docker login  -u ${env.REGISTRY_USER} -p ${env.REGISTRY_PASSWD} tonglu-docker.pkg.coding.net"
      }
    }
    stage('构建') {
      steps {
        echo '构建中...'
        sh './docker_build.sh'
        echo '构建完成.'
      }
    }
  }
}
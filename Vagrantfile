Vagrant.configure("2") do |config|
  config.vm.box = 'hashicorp/precise64'
  config.vm.hostname = 'k-imagely.com'

  config.vm.provider 'virtualbox' do |v|
    v.memory = 512
    v.cpus = 1
    v.auto_nat_dns_proxy = false
    v.customize ['modifyvm', :id, '--natdnsproxy1', 'off']
    v.customize ['modifyvm', :id, '--natdnshostresolver1', 'off']
  end

  config.vm.provision :shell, inline: 'sudo apt-get update' 
  config.vm.synced_folder '.', '/app'

  config.vm.provision :docker do |d|
    d.pull_images 'ubuntu'
  end
end

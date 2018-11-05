<?php include('config.php'); ?>
<!DOCTYPE html>
<html>
	<head>
		<title>Projeto 1</title>
		<!--Font awesome-->
		<!--Go to font awesome over google-->
		<!--go to icons within the Font awesome website-->
		<!--Have fun-->
		<link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.5.0/css/all.css" integrity="sha384-B4dIYHKNBt8Bc12p+WXckhzcICo0wtJAoU8YZTY5qE0Id1GSseTk6S+L3BlXeVIU" crossorigin="anonymous">
		<!--Go to google fonts-->
		<!--Search for a font-->
		<!--Click on the plus button and then on the bottom right button and copy the link-->
		<link href="https://fonts.googleapis.com/css?family=Open+Sans:300,400,700" rel="stylesheet">
		<link href="estilo/style.css" rel="stylesheet" />
		<!--Corrige acentuacao-->
		<meta charset="utf-8" />
		<!--Design responsivo-->
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<!--SEO keywords para pesquisa no google-->
		<meta name="keywords" content="html5, responsive, test">
		<!--SEO descricao desse site nas ferramentas de pesquisa no google-->
		<meta name="description" content="Desc do meu site">
	</head>
<body>
	<header>
		<!--Logo-->
		<div class="center">
			<div class="logo left"><a href="/">Logomarca</a></div>
			<nav class="desktop right">
				<ul>
					<li><a href="">Home   </a></li>
					<li><a href="">Sobre  </a></li>
					<li><a href="">Serviço</a></li>
					<li><a href="">Contato</a></li>
				</ul>
			</nav><!--desktop-->
			<nav class="mobile right">
				<div class="botao-menu-mobile">
					<i class="fas fa-bars"></i>
				</div><!--botao-menu-mobile-->
				<ul>
					<li><a href="">Home   </a></li>
					<li><a href="">Sobre  </a></li>
					<li><a href="">Serviço</a></li>
					<li><a href="">Contato</a></li>
				</ul>
			</nav><!--mobile-->

		<div class="clear"></div><!--clear-->

		</div><!--center-->
	</header>

	<section class="banner-principal">
		<div class="overlay"></div><!--overlay-->
		<div class="center">
			<form>
				<h2>Qual o seu e-mail?</h2>
				<input type="email" name="email" required />
				<input type="submit" name="acao" value="Cadastrar">
			</form>
		</div>
	</section><!--banner-principal-->

	<section class="descricao-autor">
		<div class="center">
			<!--A div pega 50% da largura da tela-->
			<div class="w50 left">
				<h2>Nicolas P. Lane</h2>
				<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam consectetur libero quis leo suscipit, at dapibus purus fermentum. Nulla facilisi. Suspendisse mattis pharetra interdum. Phasellus nec urna non metus lobortis tristique. In risus nulla, sodales at tortor vitae, euismod consectetur dolor. Nunc consectetur rhoncus purus id aliquet. Cras mi nulla, vulputate non facilisis in, gravida et lacus. Mauris ipsum ligula, auctor at metus eu, aliquet suscipit quam. Morbi fermentum dolor vitae orci aliquet eleifend. Pellentesque malesuada lacus et est eleifend, sit amet malesuada erat posuere. Etiam mattis, lectus quis rhoncus pulvinar, massa diam commodo lacus, a cursus tortor dolor at mi. Cras dapibus, velit et faucibus laoreet, diam lectus maximus ante, eget suscipit erat neque eget elit. Aliquam vulputate quam mi, nec faucibus erat scelerisque et. Aliquam urna massa, faucibus eu odio tempus, dignissim porttitor leo.
				</p>
			</div><!--w50-->

			<div class="w50 left">
				<!--Imagem do perfil-->
				<img class="right" src="images/perfil.jpg" />
			</div><!--w50-->

			<div class="clear"></div><!--clear-->

		</div>
	</section><!--descricao-autor-->

	<section class="especialidades">
		<!--Para trab com design responsivo-->
		<div class="center">
			<h2 class="title">Especialidades</h2>

			<div class="w33 left box-especialidade">
				<!--Icone code (awesome icons)-->
				<h3><i class="fab fa-css3"></i></h3>
				<h4>CSS3</h4>
				<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam consectetur libero quis leo suscipit, at dapibus purus fermentum. Nulla facilisi. Suspendisse mattis pharetra interdum. Phasellus nec urna non metus lobortis tristique. In risus nulla, sodales at tortor vitae, euismod consectetur dolor. Nunc consectetur rhoncus purus id aliquet. Cras mi nulla, vulputate non facilisis in, gravida et lacus. Mauris ipsum ligula, auctor at metus eu, aliquet suscipit quam. Morbi fermentum dolor vitae orci aliquet eleifend. Pellentesque malesuada lacus et est eleifend, sit amet malesuada erat posuere. Etiam mattis, lectus quis rhoncus pulvinar, massa diam commodo lacus, a cursus tortor dolor at mi. Cras dapibus, velit et faucibus laoreet, diam lectus maximus ante, eget suscipit erat neque eget elit. Aliquam vulputate quam mi, nec faucibus erat scelerisque et. Aliquam urna massa, faucibus eu odio tempus, dignissim porttitor leo.
				</p>
			</div><!--box-especialidade-->

			<div class="w33 left box-especialidade">
				<!--Icone code (awesome icons)-->
				<h3><i class="fab fa-html5"></i></h3>
				<h4>HTML5</h4>
				<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam consectetur libero quis leo suscipit, at dapibus purus fermentum. Nulla facilisi. Suspendisse mattis pharetra interdum. Phasellus nec urna non metus lobortis tristique. In risus nulla, sodales at tortor vitae, euismod consectetur dolor. Nunc consectetur rhoncus purus id aliquet. Cras mi nulla, vulputate non facilisis in, gravida et lacus. Mauris ipsum ligula, auctor at metus eu, aliquet suscipit quam. Morbi fermentum dolor vitae orci aliquet eleifend. Pellentesque malesuada lacus et est eleifend, sit amet malesuada erat posuere. Etiam mattis, lectus quis rhoncus pulvinar, massa diam commodo lacus, a cursus tortor dolor at mi. Cras dapibus, velit et faucibus laoreet, diam lectus maximus ante, eget suscipit erat neque eget elit. Aliquam vulputate quam mi, nec faucibus erat scelerisque et. Aliquam urna massa, faucibus eu odio tempus, dignissim porttitor leo.
				</p>
			</div><!--box-especialidade-->

			<div class="w33 left box-especialidade">
				<!--Icone code (awesome icons)-->
				<h3><i class="fab fa-js-square"></i></h3>
				<h4>JavaScript</h4>
				<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam consectetur libero quis leo suscipit, at dapibus purus fermentum. Nulla facilisi. Suspendisse mattis pharetra interdum. Phasellus nec urna non metus lobortis tristique. In risus nulla, sodales at tortor vitae, euismod consectetur dolor. Nunc consectetur rhoncus purus id aliquet. Cras mi nulla, vulputate non facilisis in, gravida et lacus. Mauris ipsum ligula, auctor at metus eu, aliquet suscipit quam. Morbi fermentum dolor vitae orci aliquet eleifend. Pellentesque malesuada lacus et est eleifend, sit amet malesuada erat posuere. Etiam mattis, lectus quis rhoncus pulvinar, massa diam commodo lacus, a cursus tortor dolor at mi. Cras dapibus, velit et faucibus laoreet, diam lectus maximus ante, eget suscipit erat neque eget elit. Aliquam vulputate quam mi, nec faucibus erat scelerisque et. Aliquam urna massa, faucibus eu odio tempus, dignissim porttitor leo.
				</p>
			</div><!--box-especialidade-->
		</div>

		<div class="clear"></div><!--clear-->
	</section>

	<section class="extras">
			<div class="center">
				<div class="w50 left depoimentos-container">
					<h2 class="title">Depoimentos</h2>
					<div class="left depoimentos_single">
						<p class="depoimentos_desc">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam consectetur libero quis leo suscipit, at dapibus purus fermentum. Nulla facilisi. Suspendisse mattis pharetra interdum. Phasellus nec urna non metus lobortis tristique. In risus nulla, sodales at tortor vitae, euismod consectetur dolor. Nunc consectetur rhoncus purus id aliquet. Cras mi nulla, vulputate non facilisis in, gravida et lacus. Mauris ipsum ligula, auctor at metus eu, aliquet suscipit quam. Morbi fermentum dolor vitae orci aliquet eleifend. Pellentesque malesuada lacus et est eleifend, sit amet malesuada erat posuere. Etiam mattis, lectus quis rhoncus pulvinar, massa diam commodo lacus, a cursus tortor dolor at mi. Cras dapibus, velit et faucibus laoreet, diam lectus maximus ante, eget suscipit erat neque eget elit. Aliquam vulputate quam mi, nec faucibus erat scelerisque et. Aliquam urna massa, faucibus eu odio tempus, dignissim porttitor leo.
						</p><!--depoimentos_desc-->

						<p class="nome-autor">Lorem Ipsum</p>
					</div><!--depoimentos_single-->

					<div class="left depoimentos_single">
						<p class="depoimentos_desc">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam consectetur libero quis leo suscipit, at dapibus purus fermentum. Nulla facilisi. Suspendisse mattis pharetra interdum. Phasellus nec urna non metus lobortis tristique. In risus nulla, sodales at tortor vitae, euismod consectetur dolor. Nunc consectetur rhoncus purus id aliquet. Cras mi nulla, vulputate non facilisis in, gravida et lacus. Mauris ipsum ligula, auctor at metus eu, aliquet suscipit quam. Morbi fermentum dolor vitae orci aliquet eleifend. Pellentesque malesuada lacus et est eleifend, sit amet malesuada erat posuere. Etiam mattis, lectus quis rhoncus pulvinar, massa diam commodo lacus, a cursus tortor dolor at mi. Cras dapibus, velit et faucibus laoreet, diam lectus maximus ante, eget suscipit erat neque eget elit. Aliquam vulputate quam mi, nec faucibus erat scelerisque et. Aliquam urna massa, faucibus eu odio tempus, dignissim porttitor leo.
						</p>

						<p class="nome-autor">Lorem Ipsum</p>
					</div><!--depoimentos-single-->

					<div class="left depoimentos_single">
						<p class="depoimentos_desc">Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam consectetur libero quis leo suscipit, at dapibus purus fermentum. Nulla facilisi. Suspendisse mattis pharetra interdum. Phasellus nec urna non metus lobortis tristique. In risus nulla, sodales at tortor vitae, euismod consectetur dolor. Nunc consectetur rhoncus purus id aliquet. Cras mi nulla, vulputate non facilisis in, gravida et lacus. Mauris ipsum ligula, auctor at metus eu, aliquet suscipit quam. Morbi fermentum dolor vitae orci aliquet eleifend. Pellentesque malesuada lacus et est eleifend, sit amet malesuada erat posuere. Etiam mattis, lectus quis rhoncus pulvinar, massa diam commodo lacus, a cursus tortor dolor at mi. Cras dapibus, velit et faucibus laoreet, diam lectus maximus ante, eget suscipit erat neque eget elit. Aliquam vulputate quam mi, nec faucibus erat scelerisque et. Aliquam urna massa, faucibus eu odio tempus, dignissim porttitor leo.
						</p>

						<p class="nome-autor">Lorem Ipsum</p>
					</div><!--depoitmentos_single-->
				</div><!--w50-->

				<div class="w50 left servicos-container">
					<h2 class="title">Serviços</h2>
					<div class="servicos">
						<ul>
							<li>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam consectetur libero quis leo suscipit, at dapibus purus fermentum. Nulla facilisi. Suspendisse mattis pharetra interdum. Phasellus nec urna non metus lobortis tristique. In risus nulla, sodales at tortor vitae, euismod consectetur dolor. Nunc consectetur rhoncus purus id aliquet. Cras mi nulla, vulputate non facilisis in, gravida et lacus. Mauris ipsum ligula, auctor at metus eu, aliquet suscipit quam. Morbi fermentum dolor vitae orci aliquet eleifend. Pellentesque malesuada lacus et est eleifend, sit amet malesuada erat posuere. Etiam mattis, lectus quis rhoncus pulvinar, massa diam commodo lacus, a cursus tortor dolor at mi. Cras dapibus, velit et faucibus laoreet, diam lectus maximus ante, eget suscipit erat neque eget elit. Aliquam vulputate quam mi, nec faucibus erat scelerisque et. Aliquam urna massa, faucibus eu odio tempus, dignissim porttitor leo.
</li>
							<li>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam consectetur libero quis leo suscipit, at dapibus purus fermentum. Nulla facilisi. Suspendisse mattis pharetra interdum. Phasellus nec urna non metus lobortis tristique. In risus nulla, sodales at tortor vitae, euismod consectetur dolor. Nunc consectetur rhoncus purus id aliquet. Cras mi nulla, vulputate non facilisis in, gravida et lacus. Mauris ipsum ligula, auctor at metus eu, aliquet suscipit quam. Morbi fermentum dolor vitae orci aliquet eleifend. Pellentesque malesuada lacus et est eleifend, sit amet malesuada erat posuere. Etiam mattis, lectus quis rhoncus pulvinar, massa diam commodo lacus, a cursus tortor dolor at mi. Cras dapibus, velit et faucibus laoreet, diam lectus maximus ante, eget suscipit erat neque eget elit. Aliquam vulputate quam mi, nec faucibus erat scelerisque et. Aliquam urna massa, faucibus eu odio tempus, dignissim porttitor leo.
</li>
							<li>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam consectetur libero quis leo suscipit, at dapibus purus fermentum. Nulla facilisi. Suspendisse mattis pharetra interdum. Phasellus nec urna non metus lobortis tristique. In risus nulla, sodales at tortor vitae, euismod consectetur dolor. Nunc consectetur rhoncus purus id aliquet. Cras mi nulla, vulputate non facilisis in, gravida et lacus. Mauris ipsum ligula, auctor at metus eu, aliquet suscipit quam. Morbi fermentum dolor vitae orci aliquet eleifend. Pellentesque malesuada lacus et est eleifend, sit amet malesuada erat posuere. Etiam mattis, lectus quis rhoncus pulvinar, massa diam commodo lacus, a cursus tortor dolor at mi. Cras dapibus, velit et faucibus laoreet, diam lectus maximus ante, eget suscipit erat neque eget elit. Aliquam vulputate quam mi, nec faucibus erat scelerisque et. Aliquam urna massa, faucibus eu odio tempus, dignissim porttitor leo.
</li>
						</ul>
					</div><!--servicos-->
				</div><!--w50-->

				<div class="clear"></div><!--clear-->

			</div><!--center-->
	</section>

	<footer>
		<div class="center">
			<p>NEV.i Todos os direitos reservados.</p>
		</div><!--center-->
	</footer>

	<script src="js/jquery.js"></script>
<script>
// Autoloaded function $
$(function() {
/*
	var mensagem = "Olá Mundo";
	console.log(mensagem);
	alert(mensagem);
 */
})
</script>
<script src="js/scripts.js"></script>
</body>
</html>

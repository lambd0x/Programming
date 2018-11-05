var $;
$(function() {
	// Código JS
	$('nav.mobile').click(function() {
		// O que acontece quando pressionar nav.mobile
		var listaMenu = $('nav.mobile ul');
		// Abrir menu mobile por meio do fadeIn
		/*
		if (listaMenu.is(':hidden') == true) {
			listaMenu.fadeIn();
		} else {
			listaMenu.fadeOut();
		}*/

		if (listaMenu.is(':hidden') == true) {
			listaMenu.slideToggle();
			// Ao abrir o menu troque o icone inicial de barra pelo de X
			var icone1 = $('.botao-menu-mobile i');
			icone1.removeClass('fa-bars');
			icone1.addClass('fa-times');
		} else {
			// Ao fechar o menu troque o icone de X pelo de barra
			var icone2 = $('.botao-menu-mobile i');
			icone2.removeClass('fa-times');
			icone2.addClass('fa-bars');
			listaMenu.slideToggle();
		}

	});
});

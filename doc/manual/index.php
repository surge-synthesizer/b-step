<?php

# This file passes the content of the Readme.md file in the same directory
# through the Markdown filter. You can adapt this sample code in any way
# you like.

# Install PSR-0-compatible class autoloader
spl_autoload_register(function($class){
	require preg_replace('{\\\\|_(?!.*\\\\)}', DIRECTORY_SEPARATOR, ltrim($class, '\\')).'.php';
});

# Get Markdown class
use \Michelf\Markdown;

# Read file and pass content through the Markdown parser
$text = file_get_contents('Readme.md');
$html = Markdown::defaultTransform($text);

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>	
    <?php
      $owner_url = "http://b-step.monoplugs.com";
      $html_url = "http://b-step.monoplugs.com/manual";
    
      $html_title = "B-Step Sequencer - User Manual";
      $html_title_long = "B-Step Sequencer - User Manual";
      $html_desc = "Become a Pro with B-Step 2 and learn how to create your own music live.";
      $html_desc_long = "How to create Chord Progressions, Sequencer Ratcheting. Novation Launchpad Sequencer. How to create Arpeggios. Use B-Step in Logic, Ableton Live or Cubase.";

      $html_target = "http%3A%2F%2Fb-step.monoplugs.com/manual";
      $html_image = "http%3A%2F%2Fb-step.monoplugs.com%2Fimages%2Fb-step-sequencer-artwork-100.png";
      
      $url_facebook = "https://www.facebook.com/b.step.sequencer";
      $url_twitter = "https://twitter.com/monotomys";
      $url_google = "https://plus.google.com/share?url=" . $html_target;
      $url_pinit = "http://pinterest.com/pin/create/bookmarklet/?url=" . $html_target . "&media=" . $html_image . "&is_video=false&description=" . $html_desc;
      $url_deli = "http://del.icio.us/post?url=" . $html_target . "&title=" . $html_title . "&notes=" . $html_desc;
      $url_youtube = "https://www.youtube.com/user/monotomys";
      $url_digg = "http://digg.com/submit?url=" . $html_target . "&title=" . $html_title;
    ?>
    <title><?php echo $html_title ?></title>
    
    <link rel="canonical" href="<?php echo $html_url ?>"/>
    
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <meta name="robots" content="index, follow" />
    <meta name="description" content="<?php echo $html_title ?>" />
    <meta name="keywords" content="step sequencer, sequencer, how to, howto" />
    <meta name="author" content="monotomy" />
    <meta name="robots" content="INDEX,FOLLOW" />
    <meta name="language" content="English" />
    <meta name="content-language" content="en" />
    <meta name="page-topic" content="Software, Music Software, Music Sequencer" />
    
    <meta name="date" content="2014-10-29T18:33:00+0100" scheme="YYYY-MM-DD" />

    <meta property="og:title" content="<?php echo $html_title_long ?>" />
    <meta property="og:description" content="<?php echo $html_desc ?>" />
    <meta property="og:url" content="<?php echo $owner_url ?>" />
    <meta property="og:video" content="http://youtu.be/VTKa89C-PRc" />
    <meta property="og:site_name" content="<?php echo $html_title ?>" />
    <meta itemprop="name" content="<?php echo $html_title_long ?>" />
    <meta itemprop="description" content="<?php echo $html_desc ?>" />
    
    <meta itemprop="image" content="<?php echo $owner_url ?>/images_2/b-step-sequencer-artwork-full.png" />
    <meta property="og:image" content="<?php echo $owner_url ?>/images_2/b-step-icon.png"/>
    <meta property="og:image:width" content="100" />
    <meta property="og:image:height" content="100" />
    <meta property="og:image" content="<?php echo $owner_url ?>/images_2/b-step-sequencer-artwork-1024x502.jpg"/>
    <meta property="og:image:width" content="1024" />
    <meta property="og:image:height" content="502" />

    <link rel="image_src" href="<?php echo $owner_url ?>/images_2/b-step-icon.png" />
    <link rel="image_src" href="<?php echo $owner_url ?>/images_2/b-step-sequencer-artwork-1024x502.jpg" />

    <link rel="author" href="https://plus.google.com/108841267525033741640" />

    <link rel="favourites icon" href="<?php echo $owner_url ?>/favicon2.ico?v=4" />
    <link rel="stylesheet" type="text/css" href="<?php echo $owner_url ?>/screen_2.css?v=1" />
    <link rel="stylesheet" href="<?php echo $owner_url ?>/public/fancybox/jquery.fancybox-1.3.4_v2.css" type="text/css" media="screen" />
    <script type="text/javascript" src="<?php echo $owner_url ?>/countdown/variant5/js/jquery-1.8.0.min.js"></script>
 	<!--
	<script type="text/javascript">
	 var _gaq = _gaq || [];
	 _gaq.push(['_setAccount', 'UA-47075200-1']);
	 _gaq.push(['_trackPageview']);
	 (function() {
	 var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
	 ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
	 var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
	})();
	</script>
	-->
	<style>
		.manual h1{ font-size:38px }
      .manual h2{ font-size:30px }
      .manual h3{ font-size:18px }
      .manual h4{ font-size:16px }
      .manual h5{ font-size:14px }
      .manual h6{ font-size:13px }
		.manual li, .manual ul, .manual h1, .manual h2, .manual h3, .manual h4, .manual h5, .manual h6{
	  		padding-left: 20px;
	  		text-align:left }
		.manual p, .manual li, .manual ul{
			font-weight:normal;
			font-size: 14px;
			text-align:left }
		h1 a, h2 a, h3 a, h4 a, h5 a, h6 a{
			color: orangered;
			text-decoration: none;
			text-shadow: 2px 2px 5px black }
		hr{
			border-left: 0px;
			border-top: 0px;
			border-right: 0px;
			border-bottom:solid grey 1px;
			height: 1px }
		#player { height: 20px }​
	</style>
</head>
<body>
   <div class="social">
      <a href="http://b-step.monoplugs.com"> 
			<img src="http://b-step.monoplugs.com/images_2/b-step-sequencer-home.png" alt="B-Step Sequencer Home" title="B-Step Sequencer Home" style="margin-bottom:20px" /> 
      </a> 
      <a href="<?php echo $url_facebook ?>" target="_blank" > 
			<img src="http://b-step.monoplugs.com/images_2/facebook.png" alt="B-Step Sequencer on Facebook" title="B-Step Sequencer on Facebook" /> 
      </a> 
      <a href="<?php echo $url_twitter ?>" target="_blank" > 
			<img src="http://b-step.monoplugs.com/images_2/twitter.png" alt="share B-Step Sequencer on Twitter" title="share B-Step Sequencer on Twitter" /> 
      </a>
      <a href="<?php echo $url_google ?>" target="_blank" > 
			<img src="http://b-step.monoplugs.com/images_2/google-plus.png" alt="share B-Step Sequencer on Google+" title="share B-Step Sequencer on Google+" />
      </a>
      <a href="<?php echo $url_pinit ?>" target="_blank" > 
			<img src="http://b-step.monoplugs.com/images_2/pinterest.png" alt="pin B-Step Sequencer on Pinterest" title="pin B-Step Sequencer on Pinterest" />
      </a>
      <a href="<?php echo $url_deli ?>" target="_blank" > 
			<img src="http://b-step.monoplugs.com/images_2/delicious.png" alt="mark B-Step Sequencer on Delicious" title="mark B-Step Sequencer on Delicious" /> 
      </a>
      <a href="<?php echo $url_digg ?>" target="_blank" > 
			<img src="http://b-step.monoplugs.com/images_2/digg.png" alt="share B-Step Sequencer on digg" title="share B-Step Sequencer on digg" /> 
      </a>
      <a href="<?php echo $url_youtube ?>" target="_blank" > 
			<img src="http://b-step.monoplugs.com/images_2/youtube.png" alt="B-Step Sequnecer on Youtube" title="B-Step Sequnecer on Youtube" /> 
      </a>
   </div>
	<div class="page-center" style="width:1020px">
		<div class="top-bar">
		</div>
		<div class="manual">
			<?php
			# Put HTML content in the document
			echo $html;
			?>
		</div>
		<div class="myfooter">
			<p>&copy; 2014 <a href="http://monoplugs.com"><img src="http://b-step.monoplugs.com/images/monoplugs-900.png" alt="Monoplugs Sequencer" /></a></p>
		</div>		
	</div>
   <!--
	<script type="text/javascript" src="script.js"></script>
      
        <script>
         (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
         (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
         m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
         })(window,document,'script','//www.google-analytics.com/analytics.js','ga');
         
         ga('create', 'UA-47075200-1', 'monoplugs.com');
         ga('send', 'pageview');
        </script>
        -->
    <script type="text/javascript" src="http://b-step.monoplugs.com/public/fancybox/jquery.fancybox-1.3.4.pack.js"></script>
    <script type="text/javascript" src="http://b-step.monoplugs.com/script.js"></script>
</body>
</html>
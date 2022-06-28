import * as THREE from 'three';
import shared from './shaders/shared.glsl';
import demoRenderParticlesVert from './shaders/demoRenderParticlesVert.glsl';
import demoRenderDepthVert from './shaders/demoRenderDepthVert.glsl';

var shaders = {
    shared,
    renderParticlesVertex: demoRenderParticlesVert,
    renderDepth: demoRenderDepthVert
};

export default function Demo(parameters){

    var world, scene, ambientLight, light, camera, controls, renderer, customDepthMaterial, gizmo, gui, stats, groundMesh, interactionSphereMesh, debugMesh, debugGridMesh, controller, boxSize, numParticles;

    init();
    animate();

    function init(){
        var numBodies = numParticles / 2;
        var radius = 1/numParticles * 0.5;
        boxSize = new THREE.Vector3(1, 1, 1);

        renderer = new THREE.WebGLRenderer();
        renderer.setPixelRatio( 1 );
        renderer.setSize( window.innerWidth, window.innerHeight );
        renderer.shadowMap.enabled = true;
        var container = document.getElementById( 'container' );
        container.appendChild( renderer.domElement );
        window.addEventListener( 'resize', onWindowResize, false );

        stats = new Stats();
        stats.domElement.style.position = 'absolute';
        stats.domElement.style.top = '0px';
        container.appendChild( stats.domElement );

        scene = new THREE.Scene();

        light = new THREE.DirectionalLight();
        light.castShadow = true;
        light.shadow.mapSize.width = light.shadow.mapSize.height = 1024;
        var d = 10;
        light.shadow.camera.left = - d;
        light.shadow.camera.right = d;
        light.shadow.camera.top = d;
        light.shadow.camera.bottom = - d;
        light.shadow.camera.far = 100;
        light.position.set(1,2,1);
        scene.add(light);

        ambientLight = new THREE.AmbientLight( 0x222222 );
        scene.add( ambientLight );
        renderer.setClearColor(ambientLight.color, 1.0);

        camera = new THREE.PerspectiveCamera( 30, window.innerWidth / window.innerHeight, 0.01, 100 );
        if(parameters.cameraPosition)
            camera.position.copy(parameters.cameraPosition);
        else
            camera.position.set(0,0.6,1.4);

        // Add controls
        controls = new THREE.OrbitControls( camera, renderer.domElement );
        controls.enableZoom = true;
        controls.target.set(0.0, 0.1, 0.0);
        controls.maxPolarAngle = Math.PI * 0.5;

        world = parameters.create(renderer);

        var groundMaterial = new THREE.MeshPhongMaterial( { color: 0xffffff, specular: 0x000000 } );
        groundMesh = new THREE.Mesh( new THREE.PlaneBufferGeometry( 2000, 2000 ), groundMaterial );
        groundMesh.rotation.x = - Math.PI / 2;
        groundMesh.receiveShadow = true;
        scene.add( groundMesh );

        // Create an instanced mesh for debug spheres
        var sphereGeometry = new THREE.SphereBufferGeometry(world.radius, 8, 8);
        var instances = world.maxParticles;
        var debugGeometry = new THREE.InstancedBufferGeometry();
        debugGeometry.maxInstancedCount = instances;
        for(var attributeName in sphereGeometry.attributes){
            debugGeometry.addAttribute( attributeName, sphereGeometry.attributes[attributeName].clone() );
        }
        debugGeometry.setIndex( sphereGeometry.index.clone() );
        var particleIndices = new THREE.InstancedBufferAttribute( new Float32Array( instances * 1 ), 1, 1 );
        for ( var i = 0, ul = particleIndices.count; i < ul; i++ ) {
            particleIndices.setX( i, i );
        }
        debugGeometry.addAttribute( 'particleIndex', particleIndices );
        debugGeometry.boundingSphere = null;

        // Particle spheres material / debug material - extend the phong shader in three.js
        var phongShader = THREE.ShaderLib.phong;
        var uniforms = THREE.UniformsUtils.clone(phongShader.uniforms);
        uniforms.particleLocalPosTex = { value: null };
        uniforms.posTex = { value: null };
        uniforms.posTexPrev = { value: null };
        uniforms.quatTex = { value: null };
        uniforms.quatTexPrev = { value: null };
        uniforms.interpolationValue = { value: 0 };
        var debugMaterial = new THREE.ShaderMaterial({
            uniforms: uniforms,
            vertexShader: shaders.shared + shaders.renderParticlesVertex,
            fragmentShader: phongShader.fragmentShader,
            lights: true,
            defines: {
                //USE_MAP: true,
                bodyTextureResolution: 'vec2(' + world.bodyTextureSize.toFixed(1) + ',' + world.bodyTextureSize.toFixed(1) + ')',
                resolution: 'vec2(' + world.particleTextureSize.toFixed(1) + ',' + world.particleTextureSize.toFixed(1) + ')'
            }
        });
        debugMesh = new THREE.Mesh( debugGeometry, debugMaterial );
        debugMesh.frustumCulled = false;
        var checkerTexture = new THREE.DataTexture(new Uint8Array([255,0,0,255, 255,255,255,255]), 2, 1, THREE.RGBAFormat, THREE.UnsignedByteType, THREE.UVMapping);
        checkerTexture.needsUpdate = true;
        debugMaterial.uniforms.map.value = checkerTexture;
        scene.add(debugMesh);

        initDebugGrid();

        var meshUniforms = THREE.UniformsUtils.clone(phongShader.uniforms);
        meshUniforms.particleLocalPosTex = { value: null };
        meshUniforms.posTex = { value: null };
        meshUniforms.posTexPrev = { value: null };
        meshUniforms.quatTex = { value: null };
        meshUniforms.quatTexPrev = { value: null };
        meshUniforms.interpolationValue = { value: 0 };

        // Create a depth material for rendering instances to shadow map
        customDepthMaterial = new THREE.ShaderMaterial({
            uniforms: THREE.UniformsUtils.merge([
                THREE.ShaderLib.depth.uniforms,
                meshUniforms
            ]),
            vertexShader: shaders.shared + shaders.renderDepth,
            fragmentShader: THREE.ShaderLib.depth.fragmentShader,
            defines: {
                DEPTH_PACKING: 3201,
                bodyTextureResolution: 'vec2(' + world.bodyTextureSize.toFixed(1) + ',' + world.bodyTextureSize.toFixed(1) + ')',
                resolution: 'vec2(' + world.particleTextureSize.toFixed(1) + ',' + world.particleTextureSize.toFixed(1) + ')'
            }
        });
        debugMesh.customDepthMaterial = customDepthMaterial;
        debugMesh.castShadow = true;
        debugMesh.receiveShadow = true;

        // interaction
        interactionSphereMesh = new THREE.Mesh(new THREE.SphereBufferGeometry(1,16,16), new THREE.MeshPhongMaterial({ color: 0xffffff }));
        world.getSpherePosition(0, interactionSphereMesh.position);
        scene.add(interactionSphereMesh);
        gizmo = new THREE.TransformControls( camera, renderer.domElement );
        gizmo.addEventListener( 'change', function(){
            if(this.object === interactionSphereMesh){
                world.setSpherePosition(
                    0,
                    interactionSphereMesh.position.x,
                    interactionSphereMesh.position.y,
                    interactionSphereMesh.position.z
                );
            } else if(this.object === debugGridMesh){
                world.broadphase.position.copy(debugGridMesh.position);
            }
        });
        scene.add(gizmo);
        gizmo.attach(interactionSphereMesh);
        interactionSphereMesh.castShadow = true;
        interactionSphereMesh.receiveShadow = true;

        initGUI();
    }

    function onWindowResize() {
        camera.aspect = window.innerWidth / window.innerHeight;
        camera.updateProjectionMatrix();
        renderer.setSize( window.innerWidth, window.innerHeight );
    }

    function animate( time ) {
        requestAnimationFrame( animate );
        updatePhysics( time );
        render();
        stats.update();
    }

    var prevTime, prevSpawnedBody=0;
    function updatePhysics(time){
        var deltaTime = prevTime === undefined ? 0 : (time - prevTime) / 1000;
        if(!controller.paused){
            world.step( deltaTime );
        }
        prevTime = time;
    }

    function initDebugGrid(){
        var w = world.broadphase.resolution.x * world.radius * 2;
        var h = world.broadphase.resolution.y * world.radius * 2;
        var d = world.broadphase.resolution.z * world.radius * 2;
        var boxGeom = new THREE.BoxGeometry( w, h, d );
        var wireframeMaterial = new THREE.MeshBasicMaterial({ wireframe: true });
        debugGridMesh = new THREE.Object3D();
        var mesh = new THREE.Mesh(boxGeom,wireframeMaterial);
        debugGridMesh.add(mesh);
        debugGridMesh.position.copy(world.broadphase.position);
        mesh.position.set(w/2, h/2, d/2);
        scene.add(debugGridMesh);
    }

    function updateDebugGrid(){
        debugGridMesh.position.copy(world.broadphase.position);
    }

    function render() {
        controls.update();

        // Render main scene
        updateDebugGrid();

        customDepthMaterial.uniforms.particleLocalPosTex.value =    debugMesh.material.uniforms.particleLocalPosTex.value =     world.particleLocalPositionTexture;
        customDepthMaterial.uniforms.posTex.value =                 debugMesh.material.uniforms.posTex.value =                  world.bodyPositionTexture;
        customDepthMaterial.uniforms.posTexPrev.value =             debugMesh.material.uniforms.posTexPrev.value =              world.bodyPositionPrevTexture;
        customDepthMaterial.uniforms.quatTex.value =                debugMesh.material.uniforms.quatTex.value =                 world.bodyQuaternionTexture;
        customDepthMaterial.uniforms.quatTexPrev.value =            debugMesh.material.uniforms.quatTexPrev.value =             world.bodyQuaternionPrevTexture;
        customDepthMaterial.uniforms.interpolationValue.value =            debugMesh.material.uniforms.interpolationValue.value =             world.interpolationValue;

        renderer.render( scene, camera );

        debugMesh.material.uniforms.posTex.value = null;
        debugMesh.material.uniforms.quatTex.value = null;
    }

    function initGUI(){
        controller  = {
            moreObjects: function(){ location.href = "?n=" + (numParticles*2); },
            lessObjects: function(){ location.href = "?n=" + Math.max(2,numParticles/2); },
            paused: false,
            renderParticles: false,
            renderShadows: true,
            gravity: world.gravity.y,
            interaction: 'none',
            sphereRadius: world.getSphereRadius(0)
        };

        function guiChanged() {
            world.gravity.y = controller.gravity;

            // Shadow rendering
            renderer.shadowMap.autoUpdate = controller.renderShadows;
            if(!controller.renderShadows){
                renderer.clearTarget(light.shadow.map);
            }

            // Interaction
            gizmo.detach(gizmo.object);
            scene.remove(debugGridMesh);
            switch(controller.interaction){
            case 'sphere':
                gizmo.attach(interactionSphereMesh);
                break;
            case 'broadphase':
                scene.add(debugGridMesh);
                gizmo.attach(debugGridMesh);
                break;
            }
            var r = controller.sphereRadius;
            interactionSphereMesh.scale.set(r,r,r);
            world.setSphereRadius(0,r);
        }

        gui = new dat.GUI();
        gui.add( world, "stiffness", 0, 5000, 0.1 );
        gui.add( world, "damping", 0, 100, 0.1 );
        gui.add( world, "drag", 0, 1, 0.01 );
        gui.add( world, "friction", 0, 10, 0.001 );
        gui.add( world, "fixedTimeStep", 0, 0.1, 0.001 );
        gui.add( controller, "paused" ).onChange( guiChanged );
        gui.add( controller, "gravity", -10, 10, 0.1 ).onChange( guiChanged );
        gui.add( controller, "moreObjects" );
        gui.add( controller, "lessObjects" );
        gui.add( controller, "renderParticles" ).onChange( guiChanged );
        gui.add( controller, "renderShadows" ).onChange( guiChanged );
        gui.add( controller, 'interaction', [ 'none', 'sphere', 'broadphase' ] ).onChange( guiChanged );
        gui.add( controller, 'sphereRadius', boxSize.x/10, boxSize.x/2 ).onChange( guiChanged );
        guiChanged();

        var raycaster = new THREE.Raycaster();
        var mouse = new THREE.Vector2();
        document.addEventListener('click', function( event ) {
            mouse.x = ( event.clientX / renderer.domElement.clientWidth ) * 2 - 1;
            mouse.y = - ( event.clientY / renderer.domElement.clientHeight ) * 2 + 1;
            raycaster.setFromCamera( mouse, camera );
            var intersects = raycaster.intersectObjects( [interactionSphereMesh] );
            if ( intersects.length > 0 ) {
                controller.interaction = 'sphere';
                gui.updateDisplay();
                guiChanged();
            }
        });
    }
}
